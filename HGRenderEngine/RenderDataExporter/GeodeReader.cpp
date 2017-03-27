#include "StdAfx.h"
#include "GeodeReader.h"

#include "HgLog/HgLog.h"
#include "osg\Geode"
#include "osg\Geometry"
#include "osg\Billboard"
#include "osg\Group"
#include "osg\ProxyNode"
#include "osg\Projection"
#include "osg\CoordinateSystemNode"
#include "osg\ClipNode"
#include "osg\TexGenNode"
#include "osg\LightSource"
#include "osg\Transform"
#include "osg\Camera"
#include "osg\CameraView"
#include "osg\MatrixTransform"
#include "osg\PositionAttitudeTransform"
#include "osg\Switch"
#include "osg\Sequence"
#include "osg\LOD"
#include "osg\PagedLOD"
#include "osg\ClearNode"
#include "osg\OccluderNode"
#include "osg\OcclusionQueryNode"
#include "osg\StateSet"
#include "osg\Material"
#include "osg\CullFace"

#include "hgcw\hgCst\DoorSeries.h"
#include "hgcw\hgCst\AlumStrip.h"
#include "hgcw\hgCst\Borer.h"
#include "hgcw\hgCst\BorerShow.h"
#include "hgcw\hgCst\Door.h"
#include "hgcw\hgCst\Glass.h"
#include "hgcw\hgCst\Model.h"
#include "hgcw\hgCst\Shape.h"
#include "hgcw\hgCst\SliderDoor.h"
#include "hg3d\Entity.h"
#include "hg3d\NDoorCore.h"
#include "hg3d\NDoorFrame.h"
#include "hg3d\NDoorPocket.h"
#include "hg3d\DoorWindow.h"
#include "hg3d\Girder.h"
#include "hg3d\ExtrudeMaterial.h"
#include "hg3d\LineMaterial.h"

#include "HG_SceneCenter.h"

//////////////////////////////////////////////////////////////////////////
// 三角形处理器
/** writes all primitives of a primitive-set out to a stream, decomposes quads to triangles, line-strips to lines etc */
class PrimitiveIndexWriter : public osg::PrimitiveIndexFunctor
{
public:
	PrimitiveIndexWriter(const osg::Geometry* inputGeometory,
		ListTriangle&        outTriangleVec,
		unsigned int         sectionIndex,
		unsigned int         material) :
	_sectionIndex(sectionIndex),
		_listTriangles(outTriangleVec),
		_GLDrawModeCache(0),
		_hasNormalCoords(inputGeometory->getNormalArray() != NULL),
		_hasTexCoords(inputGeometory->getTexCoordArray(0) != NULL),
		_geometory(inputGeometory),
		_lastFaceIndex(0),
		_curNormalIndex(0),
		_material(material),
		_normalBinding(inputGeometory->getNormalBinding())
	{
		if (!inputGeometory->getNormalArray() || inputGeometory->getNormalArray()->getNumElements()==0)
		{
			_normalBinding = osg::Geometry::BIND_OFF;        // Turn off binding if there is no normal data
		}
		reset();
	}

	void reset() { _curNormalIndex = 0; }

	unsigned int getNextFaceIndex() { return _lastFaceIndex; }

	virtual void setVertexArray(unsigned int, const osg::Vec2*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec3*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec4*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec2d*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec3d*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec4d*) {}

	// operator for triangles
	void writeTriangle(unsigned int i1, unsigned int i2, unsigned int i3);

	virtual void begin(GLenum mode)
	{
		_GLDrawModeCache = mode;
		_indexCache.clear();
	}

	virtual void vertex(unsigned int vert)
	{
		_indexCache.push_back(vert);
	}

	virtual void end()
	{
		if (!_indexCache.empty())
		{
			drawElements(_GLDrawModeCache, _indexCache.size(), &_indexCache.front());
		}
	}

	virtual void drawArrays(GLenum mode, GLint first, GLsizei count);

	virtual void drawElements(GLenum mode, GLsizei count, const GLubyte* indices)
	{
		drawElementsImplementation<GLubyte>(mode, count, indices);
	}

	virtual void drawElements(GLenum mode, GLsizei count, const GLushort* indices)
	{
		drawElementsImplementation<GLushort>(mode, count, indices);
	}

	virtual void drawElements(GLenum mode, GLsizei count, const GLuint* indices)
	{
		drawElementsImplementation<GLuint>(mode, count, indices);
	}

protected:

	template <typename T> void drawElementsImplementation(GLenum mode, GLsizei count, const T* indices)
	{
		if (indices==0 || count==0) return;

		typedef const T* IndexPointer;

		switch (mode)
		{
		case GL_TRIANGLES:
			{
				IndexPointer ilast = indices + count;
				for (IndexPointer iptr = indices; iptr < ilast; iptr+=3)
				{
					writeTriangle(iptr[0], iptr[1], iptr[2]);
					if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				}
				break;
			}
		case GL_TRIANGLE_STRIP:
			{
				IndexPointer iptr = indices;
				for (GLsizei i = 2; i < count; ++i, ++iptr)
				{
					if (i & 1) writeTriangle(iptr[0], iptr[2], iptr[1]);
					else       writeTriangle(iptr[0], iptr[1], iptr[2]);
				}
				if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				break;
			}
		case GL_QUADS:
			{
				IndexPointer iptr = indices;
				for (GLsizei i = 3; i < count; i += 4, iptr += 4)
				{
					writeTriangle(iptr[0], iptr[1], iptr[2]);
					writeTriangle(iptr[0], iptr[2], iptr[3]);
					if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				}
				break;
			}
		case GL_QUAD_STRIP:
			{
				IndexPointer iptr = indices;
				for (GLsizei i = 3; i < count; i += 2, iptr += 2)
				{
					writeTriangle(iptr[0], iptr[1], iptr[2]);
					writeTriangle(iptr[1], iptr[3], iptr[2]);
				}
				if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				break;
			}
		case GL_POLYGON: // treat polygons as GL_TRIANGLE_FAN
		case GL_TRIANGLE_FAN:
			{
				IndexPointer iptr = indices;
				unsigned int first = *iptr;
				++iptr;
				for (GLsizei i = 2; i < count; ++i, ++iptr)
				{
					writeTriangle(first, iptr[0], iptr[1]);
				}
				if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				break;
			}
		case GL_POINTS:
		case GL_LINES:
		case GL_LINE_STRIP:
		case GL_LINE_LOOP:
			// Not handled
			break;
		default:
			// uhm should never come to this point :)
			break;
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE_SET) ++_curNormalIndex;
	}

private:
	PrimitiveIndexWriter& operator = (const PrimitiveIndexWriter&); // { return *this; }

	unsigned int         _sectionIndex;
	ListTriangle&        _listTriangles;
	GLenum               _GLDrawModeCache;
	std::vector<GLuint>  _indexCache;
	bool                 _hasNormalCoords, _hasTexCoords;
	const osg::Geometry* _geometory;
	unsigned int         _lastFaceIndex;
	unsigned int         _curNormalIndex;
	unsigned int		 _material;
	osg::Geometry::AttributeBinding _normalBinding;
};






//////////////////////////////////////////////////////////////////////////
// 网格模型处理器


GeodeReader::GeodeReader(osg::Geode* _geode) : m_geode(_geode)
{
	m_succeedLastApply = true;
	m_currentStateSet = new osg::StateSet();
	m_listTriangles.clear();

	m_points = new osg::Vec3Array();
	m_normals = new osg::Vec3Array();
	m_uvs = new osg::Vec2Array();

	if (_geode)
	{
		processGeometery(_geode);
	}
	else	
	{
		failedApply();
	}
}


GeodeReader::~GeodeReader(void)
{
}

void GeodeReader::processGeometery(osg::Geode* _geode)
{
	unsigned int count = m_geode->getNumDrawables();
	bool texcoords = false;
	//m_material.resize(count);

	if(m_geode->getStateSet()){
		pushStateSet(m_geode->getStateSet());
	}
	for (unsigned int i = 0; i < count; ++i)
	{
		const osg::Geometry* g = m_geode->getDrawable(i)->asGeometry();
		if (g != NULL)
		{
			//解析当前网格模型 geometry

			//保存state是为了提取材质
			pushStateSet(g->getStateSet());

			//保存多边形三角化顺序
			createListTriangle(g, m_listTriangles, texcoords, i);

			popStateSet(g->getStateSet());

			//创建顶点集合
			createListVerts(g);

			//创建法线集合
			createListNormals(g);

			//创建UV集合
			createListUVs(g);

			//创建网格模型保存到外部
			saveMesh(g,i);
		}
	}
	//debugTriangleList();
	if(m_geode->getStateSet()){
		popStateSet(m_geode->getStateSet());
	}
}

void GeodeReader::createListTriangle(const osg::Geometry* geo, ListTriangle& listTriangles, bool& texcoords,unsigned int& drawable_n)
{
	unsigned int nbVertices = 0;
	texcoords = false;
	{
		const osg::Array * vecs = geo->getVertexArray();
		if (vecs)
		{
			nbVertices = vecs->getNumElements();

			// Texture coords
			const osg::Array * texvec = geo->getTexCoordArray(0);
			if (texvec)
			{
				unsigned int nb = texvec->getNumElements();
				if (nb == nbVertices) texcoords = true;
			}
		}
	}

	if (nbVertices==0) return;

	int material = getMaterialIndex(geo, m_currentStateSet.get());

	PrimitiveIndexWriter pif(geo, listTriangles, drawable_n, material);
	for (unsigned int iPrimSet = 0; iPrimSet < geo->getNumPrimitiveSets(); ++iPrimSet) //Fill the Triangle List
	{
		const osg::PrimitiveSet* ps = geo->getPrimitiveSet(iPrimSet);
		const_cast<osg::PrimitiveSet*>(ps)->accept(pif);
	}
}

int GeodeReader::getMaterialIndex(const osg::Geometry* geo, const osg::StateSet* ss)
{
	const osg::Material* osgMaterial = dynamic_cast<const osg::Material*>(ss->getAttribute(osg::StateAttribute::MATERIAL));
	const osg::Texture* osgTexture = dynamic_cast<const osg::Texture*>(ss->getTextureAttribute(0, osg::StateAttribute::TEXTURE));
	const osg::Array* osgColorArr = geo->getColorArray();

	if (osgTexture)
	{
		//TODO: 保存图像
		const osg::Image* img = osgTexture->getImage(0);
		//HGLOG_DEBUG("img src:%s",img->getFileName().c_str());
		GeodeMatrial mat_image(img->getFileName());
		for (UINT i = 0; i < m_material.size() ; i++)
		{
			if (m_material.at(i).Type() == GeodeMatrial::image)
			{
				if( mat_image == m_material.at(i) )
				{
					return i;
				}
			}
		}

		m_material.push_back(mat_image);	
		return m_material.size() - 1;
	}
	if (osgMaterial)
	{
		//TODO: 取颜色，取正反面，并应用起来
		osg::Material::ColorMode mode = osgMaterial->getColorMode();
		const osg::StateAttribute* attribute = ss->getAttribute(osg::StateAttribute::CULLFACE);
		if (attribute)
		{
			osg::CullFace::Mode mode = static_cast<const osg::CullFace*>(attribute)->getMode();
			if (mode == osg::CullFace::FRONT_AND_BACK)
			{
				HGLOG_DEBUG("llFace::FRONT_AND_BACK");
			}
			else if (mode == osg::CullFace::FRONT)
			{
				HGLOG_DEBUG("llFace::FRONT");
			}
			else if (mode == osg::CullFace::BACK)
			{
				HGLOG_DEBUG("llFace::BACK");
			}
		}

		//获得物体材质颜色
		osg::Vec4 color = osgMaterial->getDiffuse(osg::Material::FRONT);
		GeodeMatrial mat_color(color.r(),color.g(),color.b(),color.a());
		for (UINT i = 0; i < m_material.size() ; i++)
		{
			if( mat_color == m_material.at(i) )
			{
				return i;
			}
		}
		m_material.push_back(mat_color);
		return m_material.size() - 1;
		
	}
	else
	{
		GeodeMatrial defaultMaterial;
		//没有材质用白色
		for (UINT i = 0; i < m_material.size() ; i++)
		{
			if(m_material.at(i) == defaultMaterial)
			{
				return i;
			}
		}
		m_material.push_back(defaultMaterial);
		return m_material.size() - 1;
	}

}

void GeodeReader::pushStateSet(const osg::StateSet* ss)
{
	if (ss)
	{
		// Save our current stateset
		m_stateSetStack.push(m_currentStateSet.get());

		// merge with node stateset
		m_currentStateSet = static_cast<osg::StateSet*>(
			m_currentStateSet->clone(osg::CopyOp::SHALLOW_COPY));
		m_currentStateSet->merge(*ss);
	}
}

void GeodeReader::popStateSet(const osg::StateSet* ss)
{
	if (ss)
	{
		// restore the previous stateset
		m_currentStateSet = m_stateSetStack.top();
		m_stateSetStack.pop();
	}
}

void GeodeReader::createListUVs(const osg::Geometry* g)
{
	m_uvs->resize(m_listTriangles.size()*3);
	const osg::Array * basetexcoords = g->getTexCoordArray(0);
	if (basetexcoords && basetexcoords->getNumElements()>0)
	{
		for (UINT i = 0; i < m_listTriangles.size() ; i++)
		{
			//FbxVector2 texcoord;
			if (basetexcoords->getType() == osg::Array::Vec2ArrayType)
			{
				const osg::Vec2  vec1 = (*static_cast<const osg::Vec2Array  *>(basetexcoords))[m_listTriangles.at(i).first.t1];
				const osg::Vec2  vec2 = (*static_cast<const osg::Vec2Array  *>(basetexcoords))[m_listTriangles.at(i).first.t2];
				const osg::Vec2  vec3 = (*static_cast<const osg::Vec2Array  *>(basetexcoords))[m_listTriangles.at(i).first.t3];

				(*m_uvs)[m_listTriangles.at(i).first.t1].set(vec1.x(), vec1.y());
				(*m_uvs)[m_listTriangles.at(i).first.t2].set(vec2.x(), vec2.y());
				(*m_uvs)[m_listTriangles.at(i).first.t3].set(vec3.x(), vec3.y());

// 				HGLOG_DEBUG("vertex( %f, %f )",vec1.x(), vec1.y());
// 				HGLOG_DEBUG("vertex( %f, %f )",vec2.x(), vec2.y());
// 				HGLOG_DEBUG("vertex( %f, %f )",vec3.x(), vec3.y());
			}
			else if (basetexcoords->getType() == osg::Array::Vec2dArrayType)
			{
				const osg::Vec2d  vec1 = (*static_cast<const osg::Vec2dArray  *>(basetexcoords))[m_listTriangles.at(i).first.t1];
				const osg::Vec2d  vec2 = (*static_cast<const osg::Vec2dArray  *>(basetexcoords))[m_listTriangles.at(i).first.t2];
				const osg::Vec2d  vec3 = (*static_cast<const osg::Vec2dArray  *>(basetexcoords))[m_listTriangles.at(i).first.t3];

				(*m_uvs)[m_listTriangles.at(i).first.t1].set(vec1.x(), vec1.y());
				(*m_uvs)[m_listTriangles.at(i).first.t2].set(vec2.x(), vec2.y());
				(*m_uvs)[m_listTriangles.at(i).first.t3].set(vec3.x(), vec3.y());

// 				HGLOG_DEBUG("vertex( %f, %f )",vec1.x(), vec1.y());
// 				HGLOG_DEBUG("vertex( %f, %f )",vec2.x(), vec2.y());
// 				HGLOG_DEBUG("vertex( %f, %f )",vec3.x(), vec3.y());
			}
			else
			{
				OSG_NOTIFY(osg::FATAL) << "Texture coords array is not Vec2 or Vec2d. Not implemented" << std::endl;
				throw "Texture coords array is not Vec2 or Vec2d. Not implemented";
				//_succeeded = false;
				//return;
			}

			//lUVDiffuseLayer->GetDirectArray().SetAt(it->second, texcoord);
			//HGLOG_DEBUG("uv( point %d )",it->second);
		}
	}
}

void GeodeReader::createListVerts(const osg::Geometry* g)
{
	m_points->resize(m_listTriangles.size()*3);
	if (g->getVertexArray())
	{
		const osg::Array * basevecs = g->getVertexArray();
		assert(basevecs);
		if (!basevecs || basevecs->getNumElements()==0)
		{
			HGLOG_WARN("顶点集合不存在");
			return;
		}
		//FbxVector4 vertex;
		for (UINT i = 0; i < m_listTriangles.size() ; i++)
		{
			if (basevecs->getType() == osg::Array::Vec3ArrayType)
			{
				osg::Vec3  vec1 = (*static_cast<const osg::Vec3Array  *>(basevecs))[m_listTriangles.at(i).first.t1];
				osg::Vec3  vec2 = (*static_cast<const osg::Vec3Array  *>(basevecs))[m_listTriangles.at(i).first.t2];
				osg::Vec3  vec3 = (*static_cast<const osg::Vec3Array  *>(basevecs))[m_listTriangles.at(i).first.t3];

				(*m_points)[m_listTriangles.at(i).first.t1].set(vec1.x(), vec1.y(), vec1.z());
				(*m_points)[m_listTriangles.at(i).first.t2].set(vec2.x(), vec2.y(), vec2.z());
				(*m_points)[m_listTriangles.at(i).first.t3].set(vec3.x(), vec3.y(), vec3.z());

// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec1.x(), vec1.y(), vec1.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec2.x(), vec2.y(), vec2.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec3.x(), vec3.y(), vec3.z());
			}
			else if (basevecs->getType() == osg::Array::Vec3dArrayType)
			{
				osg::Vec3d  vec1 = (*static_cast<const osg::Vec3dArray  *>(basevecs))[m_listTriangles.at(i).first.t1];
				osg::Vec3d  vec2 = (*static_cast<const osg::Vec3dArray  *>(basevecs))[m_listTriangles.at(i).first.t2];
				osg::Vec3d  vec3 = (*static_cast<const osg::Vec3dArray  *>(basevecs))[m_listTriangles.at(i).first.t3];

				(*m_points)[m_listTriangles.at(i).first.t1].set(vec1.x(), vec1.y(), vec1.z());
				(*m_points)[m_listTriangles.at(i).first.t2].set(vec2.x(), vec2.y(), vec2.z());
				(*m_points)[m_listTriangles.at(i).first.t3].set(vec3.x(), vec3.y(), vec3.z());

// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec1.x(), vec1.y(), vec1.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec2.x(), vec2.y(), vec2.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec3.x(), vec3.y(), vec3.z());
			}
			else
			{
				OSG_NOTIFY(osg::FATAL) << "Vertex array is not Vec3 or Vec3d. Not implemented" << std::endl;
				throw "Vertex array is not Vec3 or Vec3d. Not implemented";
				//_succeeded = false;
				//return;
			}
		}
		
	}
}

void GeodeReader::createListNormals(const osg::Geometry* g)
{
	m_normals->resize(m_listTriangles.size()*3);
	const osg::Array * basenormals = g->getNormalArray();

	if (basenormals && basenormals->getNumElements()>0)
	{
		//FbxVector4 normal;
		for (UINT i = 0; i < m_listTriangles.size() ; i++)
		{
			if (basenormals->getType() == osg::Array::Vec3ArrayType)
			{
				const osg::Vec3  vec1 = (*static_cast<const osg::Vec3Array  *>(basenormals))[m_listTriangles.at(i).first.normalIndex1];
				const osg::Vec3  vec2 = (*static_cast<const osg::Vec3Array  *>(basenormals))[m_listTriangles.at(i).first.normalIndex2];
				const osg::Vec3  vec3 = (*static_cast<const osg::Vec3Array  *>(basenormals))[m_listTriangles.at(i).first.normalIndex3];

				(*m_normals)[m_listTriangles.at(i).first.normalIndex1].set(vec1.x(), vec1.y(), vec1.z());
				(*m_normals)[m_listTriangles.at(i).first.normalIndex2].set(vec2.x(), vec2.y(), vec2.z());
				(*m_normals)[m_listTriangles.at(i).first.normalIndex3].set(vec3.x(), vec3.y(), vec3.z());

// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec1.x(), vec1.y(), vec1.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec2.x(), vec2.y(), vec2.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec3.x(), vec3.y(), vec3.z());

			}
			else if (basenormals->getType() == osg::Array::Vec3dArrayType)
			{
				const osg::Vec3d  vec1 = (*static_cast<const osg::Vec3dArray  *>(basenormals))[m_listTriangles.at(i).first.normalIndex1];
				const osg::Vec3d  vec2 = (*static_cast<const osg::Vec3dArray  *>(basenormals))[m_listTriangles.at(i).first.normalIndex2];
				const osg::Vec3d  vec3 = (*static_cast<const osg::Vec3dArray  *>(basenormals))[m_listTriangles.at(i).first.normalIndex3];

				(*m_normals)[m_listTriangles.at(i).first.normalIndex1].set(vec1.x(), vec1.y(), vec1.z());
				(*m_normals)[m_listTriangles.at(i).first.normalIndex2].set(vec2.x(), vec2.y(), vec2.z());
				(*m_normals)[m_listTriangles.at(i).first.normalIndex3].set(vec3.x(), vec3.y(), vec3.z());

// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec1.x(), vec1.y(), vec1.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec2.x(), vec2.y(), vec2.z());
// 				HGLOG_DEBUG("vertex( %f, %f, %f)",vec3.x(), vec3.y(), vec3.z());

			}
			else
			{
				OSG_NOTIFY(osg::FATAL) << "Normal array is not Vec3 or Vec3d. Not implemented" << std::endl;
				throw "Normal array is not Vec3 or Vec3d. Not implemented";
				//_succeeded = false;
				//return;
			}
			//HGLOG_DEBUG("normal( point %d )",it->second);

			//switch (pGeometry->getNormalBinding())
			//{
			//case osg::Geometry::BIND_PER_PRIMITIVE_SET:
			//case osg::Geometry::BIND_PER_PRIMITIVE:
			//case osg::Geometry::BIND_PER_VERTEX:
			//    break;
			//}
			//lLayerElementNormal->GetDirectArray().SetAt(it->second, normal);
		}
	}
}

void GeodeReader::saveMesh(const osg::Geometry* g,UINT drawable_n)
{
	//////////////////////////////////////////////////////////////////////////
	//保存网格模型

	HG_Mesh mesh;	
	//verts 顶点集合
	for (UINT i = 0; i < get_points().get()->size() ; i++)
	{
		osg::Vec3 vec = get_points().get()->at(i);
		mesh.ref_verts().push_back(HG_Vec3(vec.x(),vec.y(),vec.z()));
	}
	ref_points()->clear();

	//normal 法线集合
	for (UINT i = 0; i < get_normals().get()->size() ; i++)
	{
		osg::Vec3 vec = get_normals().get()->at(i);
		mesh.ref_normals().push_back(HG_Vec3(vec.x(),vec.y(),vec.z()));
	}
	ref_normals()->clear();

	//uvs 纹理集合
	for (UINT i = 0; i < get_uvs().get()->size() ; i++)
	{
		osg::Vec2 vec = get_uvs().get()->at(i);
		mesh.ref_uvs().push_back(HG_Vec2(vec.x(),vec.y()));
	}
	ref_uvs()->clear();

	//三角形面
	int checkMaterialIndex = -2;
	for (UINT triangle_i = 0; triangle_i < get_listTriangles().size() ; triangle_i++)
	{
		Triangle tri = get_listTriangles().at(triangle_i).first;
		UINT section = get_listTriangles().at(triangle_i).second;

		//三角形面
		mesh.ref_faces().push_back(HG_MeshTriangle(tri.t1,tri.t2,tri.t3));
		if (checkMaterialIndex == -2)
		{
			checkMaterialIndex = tri.material;
		}
		if (checkMaterialIndex != tri.material)
		{
			HGLOG_WARN("在同一个网格模型中混杂着其他材质");
		}
	}
	ref_listTriangles().clear();

	//mesh唯一码获取方式
	{
		CString mm;
		mm.Format("mesh_%08X_scetion%02d", g, drawable_n);
		mesh.set_unique_code(mm.GetBuffer());
		HG_SceneCenter::inst().addMesh(mesh);
	}



	//////////////////////////////////////////////////////////////////////////
	//保存材质

	//材质集合
	for (UINT material_i = 0; material_i < get_material().size() ; material_i++)
	{
		HG_Material material;
		GeodeMatrial gmat = get_material().at(material_i);
		if (gmat.Type() == GeodeMatrial::image)
		{
			//TODO: 查找有没有高清材质
			material.set_type(HG_Material::image);
			material.set_image(gmat.Image());
		}
		else if (gmat.Type() == GeodeMatrial::color)
		{
			material.set_type(HG_Material::color);
			material.set_color(HG_Vec4(gmat.Color().r(),gmat.Color().g(),gmat.Color().b(),gmat.Color().a()));
		}
		else if (gmat.Type() == GeodeMatrial::empty)
		{
			material.set_type(HG_Material::color);
			material.set_unique_code("material_default_empty_white");
		}

		//创建唯一标识码
		if (material.get_unique_code().empty())
		{
			CString mm;
			mm.Format("material_%08X_section%02d_matIndex%02d", (UINT)(g), drawable_n, material_i);
			material.set_unique_code(mm.GetBuffer());
		}
		HG_SceneCenter::inst().addMaterial(material);

		//////////////////////////////////////////////////////////////////////////
		// 物体实例

		//世界坐标矩阵
		osg::Matrix matrixWorld = g->getWorldMatrices().at(0);
		HG_Mat worldMatrix = HG_Mat(
			HG_Vec4(matrixWorld(0,0),matrixWorld(0,1),matrixWorld(0,2),matrixWorld(0,3)),
			HG_Vec4(matrixWorld(1,0),matrixWorld(1,1),matrixWorld(1,2),matrixWorld(1,3)),
			HG_Vec4(matrixWorld(2,0),matrixWorld(2,1),matrixWorld(2,2),matrixWorld(2,3)),
			HG_Vec4(matrixWorld(3,0),matrixWorld(3,1),matrixWorld(3,2),matrixWorld(3,3))
		);
		HG_SceneCenter::inst().addMeshUseMaterial(HG_MeshInstance(mesh.get_unique_code(),material.get_unique_code(),worldMatrix));
	}
	ref_material().clear();
}





void GeodeReader::buildFaces(const osg::Geode& geo,ListTriangle& listTriangles,bool texcoords)
{
	MapIndices index_vert;
	unsigned int i = 0;
	for (ListTriangle::iterator it = listTriangles.begin(); it != listTriangles.end(); ++it, ++i) //Go through the triangle list to define meshs
	{
		addPolygon(/*mesh,*/ index_vert, it->first, it->second);
	}
	setControlPointAndNormalsAndUV(geo, index_vert, texcoords/*, mesh*/);
}

void GeodeReader::setControlPointAndNormalsAndUV(const osg::Geode& geo,	MapIndices& index_vert,bool              texcoords)
{
	m_points->resize(index_vert.size());
	m_normals->resize(index_vert.size());
	m_uvs->resize(index_vert.size());

	for (MapIndices::iterator it = index_vert.begin(); it != index_vert.end(); ++it)
	{
		const osg::Geometry* pGeometry = geo.getDrawable(it->first.drawableIndex)->asGeometry();
		unsigned int vertexIndex = it->first.vertexIndex;
		unsigned int normalIndex = it->first.normalIndex;

		if (texcoords)
		{
			const osg::Array * basetexcoords = pGeometry->getTexCoordArray(0);
			if (basetexcoords && basetexcoords->getNumElements()>0)
			{
				//FbxVector2 texcoord;
				if (basetexcoords->getType() == osg::Array::Vec2ArrayType)
				{
					const osg::Vec2 & vec = (*static_cast<const osg::Vec2Array *>(basetexcoords))[vertexIndex];
					(*m_uvs)[it->second].set(vec.x(), vec.y());
					//HGLOG_DEBUG("uv( %f, %f)",vec.x(), vec.y());
				}
				else if (basetexcoords->getType() == osg::Array::Vec2dArrayType)
				{
					const osg::Vec2d & vec = (*static_cast<const osg::Vec2dArray *>(basetexcoords))[vertexIndex];
					(*m_uvs)[it->second].set(vec.x(), vec.y());
					//HGLOG_DEBUG("uv( %f, %f)",vec.x(), vec.y());
				}
				else
				{
					OSG_NOTIFY(osg::FATAL) << "Texture coords array is not Vec2 or Vec2d. Not implemented" << std::endl;
					throw "Texture coords array is not Vec2 or Vec2d. Not implemented";
					//_succeeded = false;
					//return;
				}

				//lUVDiffuseLayer->GetDirectArray().SetAt(it->second, texcoord);
				//HGLOG_DEBUG("uv( point %d )",it->second);
			}
		}
	}
}

void GeodeReader::addPolygon(/*FbxMesh * mesh,*/ MapIndices & index_vert, const Triangle & tri, unsigned int drawableNum)
{
	addPolygont3(index_vert, tri.t1, tri.normalIndex1, drawableNum);
	addPolygont3(index_vert, tri.t2, tri.normalIndex2, drawableNum);
	addPolygont3(index_vert, tri.t3, tri.normalIndex3, drawableNum);

	// 	mesh->AddPolygon(addPolygon(index_vert, tri.t1, tri.normalIndex1, drawableNum));
	// 	mesh->AddPolygon(addPolygon(index_vert, tri.t2, tri.normalIndex2, drawableNum));
	// 	mesh->AddPolygon(addPolygon(index_vert, tri.t3, tri.normalIndex3, drawableNum));
}

unsigned int GeodeReader::addPolygont3(MapIndices & index_vert, unsigned int vertIndex, unsigned int normIndex, unsigned int drawableNum)
{
	VertexIndex vert(vertIndex, drawableNum, normIndex);
	MapIndices::iterator itIndex = index_vert.find(vert);
	if (itIndex == index_vert.end())
	{
		unsigned int indexMesh = index_vert.size();
		index_vert.insert(std::make_pair(vert, indexMesh));
		return indexMesh;
	}
	return itIndex->second;
}

void PrimitiveIndexWriter::writeTriangle(unsigned int i1, unsigned int i2, unsigned int i3)
{
	Triangle triangle;
	triangle.t1 = i1;
	triangle.t2 = i2;
	triangle.t3 = i3;
	if (_normalBinding == osg::Geometry::BIND_PER_VERTEX){
		triangle.normalIndex1 = i1;
		triangle.normalIndex2 = i2;
		triangle.normalIndex3 = i3;
	}
	else{
		triangle.normalIndex1 = _curNormalIndex;
		triangle.normalIndex2 = _curNormalIndex;
		triangle.normalIndex3 = _curNormalIndex;
	}
	triangle.material = _material;
	_listTriangles.push_back(std::make_pair(triangle, _sectionIndex));
}

void PrimitiveIndexWriter::drawArrays(GLenum mode,GLint first,GLsizei count)
{
	unsigned int pos=first;
	switch (mode)
	{
	case GL_TRIANGLES:
		for (GLsizei i = 2; i < count; i += 3, pos += 3)
		{
			writeTriangle(pos, pos + 1, pos + 2);
			if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		}
		break;
	case GL_TRIANGLE_STRIP:
		for (GLsizei i = 2; i < count; ++i, ++pos)
		{
			if (i & 1) writeTriangle(pos, pos + 2, pos + 1);
			else       writeTriangle(pos, pos + 1, pos + 2);
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		break;
	case GL_QUADS:
		for (GLsizei i = 3; i < count; i += 4, pos += 4)
		{
			writeTriangle(pos, pos + 1, pos + 2);
			writeTriangle(pos, pos + 2, pos + 3);
			if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		}
		break;
	case GL_QUAD_STRIP:
		for (GLsizei i = 3; i < count; i += 2, pos += 2)
		{
			writeTriangle(pos, pos + 1, pos + 2);
			writeTriangle(pos + 1, pos + 3, pos + 2);
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		break;
	case GL_POLYGON: // treat polygons as GL_TRIANGLE_FAN
	case GL_TRIANGLE_FAN:
		pos = first + 1;
		for (GLsizei i = 2; i < count; ++i, ++pos)
		{
			writeTriangle(first, pos, pos+1);
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		break;
	case GL_POINTS:
	case GL_LINES:
	case GL_LINE_STRIP:
	case GL_LINE_LOOP:
	default:
		OSG_WARN << "WriterNodeVisitor :: can't handle mode " << mode << std::endl;
		break;
	}
	if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE_SET) ++_curNormalIndex;
}




void GeodeReader::debugTriangleList()
{
	for (UINT i = 0; i < m_listTriangles.size() ; i++)
	{
		HGLOG_DEBUG("vertsIndex{%d,%d,%d},normalIndex{%d,%d,%d},face:%d,matrialimg:%d"
			,m_listTriangles.at(i).first.t1,m_listTriangles.at(i).first.t2,m_listTriangles.at(i).first.t3
			,m_listTriangles.at(i).first.normalIndex1,m_listTriangles.at(i).first.normalIndex2,m_listTriangles.at(i).first.normalIndex3
			,m_listTriangles.at(i).second,m_listTriangles.at(i).first.material);
	}
}

void GeodeReader::debugGeode()
{
	HGLOG_DEBUG("mesh verts");
	for (UINT vert_i = 0; vert_i < m_points->size() ; vert_i++)
	{
		osg::Vec3 vec = m_points->at(vert_i);
		HGLOG_DEBUG("vertex( %f, %f, %f)",vec.x(), vec.y(), vec.z());
	}

	HGLOG_DEBUG("mesh normal");
	for (UINT vert_i = 0; vert_i < m_normals->size() ; vert_i++)
	{
		osg::Vec3 vec = m_normals->at(vert_i);
		HGLOG_DEBUG("normal( %f, %f, %f)",vec.x(), vec.y(), vec.z());
	}

	HGLOG_DEBUG("mesh uv");
	for (UINT vert_i = 0; vert_i < m_uvs->size() ; vert_i++)
	{
		osg::Vec2 vec = m_uvs->at(vert_i);
		HGLOG_DEBUG("uv( %f, %f )",vec.x(), vec.y());
	}

	debugTriangleList();

	HGLOG_DEBUG("face img");
	for (UINT vert_i = 0; vert_i < m_material.size() ; vert_i++)
	{
		HGLOG_DEBUG("material ( %s )",m_material.at(vert_i).toString().c_str());
	}
}