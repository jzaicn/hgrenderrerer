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









GeodeReader::GeodeReader(osg::Geode* _geode)
{
	_succeedLastApply = true;
	_currentStateSet = new osg::StateSet();

	processGeometery(geode);
}


GeodeReader::~GeodeReader(void)
{
}

void GeodeReader::processGeometery(osg::Geode* _geode)
{
	unsigned int count = geode->getNumDrawables();
	ListTriangle listTriangles;
	bool texcoords = false;

	if(geode->getStateSet()){
		pushStateSet(geode->getStateSet());
	}
	for (unsigned int i = 0; i < count; ++i)
	{
		const osg::Geometry* g = geode->getDrawable(i)->asGeometry();
		if (g != NULL)
		{
			pushStateSet(g->getStateSet());
			//TODO: 保存多边形三角化顺序
			createListTriangle(g, listTriangles, texcoords, i);
			popStateSet(g->getStateSet());
		}
	}

	for (int i = 0; i < listTriangles.size() ; i++)
	{
		HGLOG_DEBUG("vertsIndex{%d,%d,%d},normalIndex{%d,%d,%d},face:%d"
			,listTriangles.at(i).first.t1,listTriangles.at(i).first.t2,listTriangles.at(i).first.t3
			,listTriangles.at(i).first.normalIndex1,listTriangles.at(i).first.normalIndex2,listTriangles.at(i).first.normalIndex3
			,listTriangles.at(i).second);
	}


	if(geode->getStateSet()){
		popStateSet(geode->getStateSet());
	}
	if (count > 0)
	{
		buildFaces(*geode, listTriangles, texcoords);
	}
}

void GeodeReader::pushStateSet(const osg::StateSet* ss)
{
	if (ss)
	{
		// Save our current stateset
		_stateSetStack.push(_currentStateSet.get());

		// merge with node stateset
		_currentStateSet = static_cast<osg::StateSet*>(
			_currentStateSet->clone(osg::CopyOp::SHALLOW_COPY));
		_currentStateSet->merge(*ss);
	}
}


void GeodeReader::popStateSet(const osg::StateSet* ss)
{
	if (ss)
	{
		// restore the previous stateset
		_currentStateSet = _stateSetStack.top();
		_stateSetStack.pop();
	}
}


int GeodeReader::getMaterialIndex(const osg::StateSet* ss)
{
	const osg::Material* osgMaterial = dynamic_cast<const osg::Material*>(ss->getAttribute(osg::StateAttribute::MATERIAL));
	const osg::Texture* osgTexture = dynamic_cast<const osg::Texture*>(ss->getTextureAttribute(0, osg::StateAttribute::TEXTURE));

	if (osgMaterial)
	{
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
	}
	if (osgTexture)
	{
		//TODO: 保存图像
		const osg::Image* img = osgTexture->getImage(0);
		HGLOG_DEBUG("img src:%s",img->getFileName().c_str());
	}

	return -1;
}


void GeodeReader::createListTriangle(const osg::Geometry* geo,
	ListTriangle&        listTriangles,
	bool&                texcoords,
	unsigned int&        drawable_n)
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

	int material = getMaterialIndex(_currentStateSet.get());

	PrimitiveIndexWriter pif(geo, listTriangles, drawable_n, material);
	for (unsigned int iPrimSet = 0; iPrimSet < geo->getNumPrimitiveSets(); ++iPrimSet) //Fill the Triangle List
	{
		const osg::PrimitiveSet* ps = geo->getPrimitiveSet(iPrimSet);
		const_cast<osg::PrimitiveSet*>(ps)->accept(pif);
	}
}


void GeodeReader::buildFaces(const osg::Geode& geo,
	ListTriangle&     listTriangles,
	bool              texcoords)
{
	MapIndices index_vert;
	// 	FbxMesh* mesh = FbxMesh::Create(_pSdkManager, geo.getName().c_str());
	// 	_curFbxNode->AddNodeAttribute(mesh);
	// 	_curFbxNode->SetShadingMode(FbxNode::eTextureShading);
	// 	FbxLayer* lLayer = mesh->GetLayer(0);
	// 	if (lLayer == NULL)
	// 	{
	// 		mesh->CreateLayer();
	// 		lLayer = mesh->GetLayer(0);
	// 	}
	// 	setLayerTextureAndMaterial(mesh);
	// 	lLayer->GetTextures(FbxLayerElement::eTextureDiffuse)->GetIndexArray().SetCount(listTriangles.size());
	// 	lLayer->GetMaterials()->GetIndexArray().SetCount(listTriangles.size());

	unsigned int i = 0;
	for (ListTriangle::iterator it = listTriangles.begin(); it != listTriangles.end(); ++it, ++i) //Go through the triangle list to define meshs
	{
		//begin polygon
		addPolygon(/*mesh,*/ index_vert, it->first, it->second);
		//end polygon

		//		//根据是否有材质，和材质序号，决定在哪个section开始画一个三角形面
		// 		if (it->first.material == -1)
		// 		{
		// 			mesh->BeginPolygon();
		// 		}
		// 		else
		// 		{
		// 			mesh->BeginPolygon(i);
		// 			lLayer->GetTextures(FbxLayerElement::eTextureDiffuse)->GetIndexArray().SetAt(i, it->first.material);
		// 			lLayer->GetMaterials()->GetIndexArray().SetAt(i, it->first.material);
		// 		}
		// 		addPolygon(mesh, index_vert, it->first, it->second);
		// 		mesh->EndPolygon();
	}
	setControlPointAndNormalsAndUV(geo, index_vert, texcoords/*, mesh*/);
}

void GeodeReader::setControlPointAndNormalsAndUV(const osg::Geode& geo,
	MapIndices&       index_vert,
	bool              texcoords)
	// 	FbxMesh*         mesh)
{
	// 	mesh->InitControlPoints(index_vert.size());
	// 	FbxLayerElementNormal* lLayerElementNormal= FbxLayerElementNormal::Create(mesh, "");
	// 	// For now, FBX writer only supports normals bound per vertices
	// 	lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
	// 	lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
	// 	lLayerElementNormal->GetDirectArray().SetCount(index_vert.size());
	// 	mesh->GetLayer(0)->SetNormals(lLayerElementNormal);
	// 	FbxLayerElementUV* lUVDiffuseLayer = FbxLayerElementUV::Create(mesh, "DiffuseUV");

	if (texcoords)
	{
		//TODO: 设置UVs
		//HGLOG_DEBUG("uvs nums:%d",geo.getDrawable(0)->_useVertexBufferObjects);
		// 		lUVDiffuseLayer->SetMappingMode(FbxLayerElement::eByControlPoint);
		// 		lUVDiffuseLayer->SetReferenceMode(FbxLayerElement::eDirect);
		// 		lUVDiffuseLayer->GetDirectArray().SetCount(index_vert.size());
		// 		mesh->GetLayer(0)->SetUVs(lUVDiffuseLayer, FbxLayerElement::eTextureDiffuse);


	}

	for (MapIndices::iterator it = index_vert.begin(); it != index_vert.end(); ++it)
	{
		const osg::Geometry* pGeometry = geo.getDrawable(it->first.drawableIndex)->asGeometry();
		unsigned int vertexIndex = it->first.vertexIndex;
		unsigned int normalIndex = it->first.normalIndex;

		const osg::Array * basevecs = pGeometry->getVertexArray();
		assert(basevecs);
		if (!basevecs || basevecs->getNumElements()==0)
		{
			//OSG_NOTIFY()
			continue;
		}
		//FbxVector4 vertex;
		if (basevecs->getType() == osg::Array::Vec3ArrayType)
		{
			const osg::Vec3  & vec = (*static_cast<const osg::Vec3Array  *>(basevecs))[vertexIndex];
			//vertex.Set(vec.x(), vec.y(), vec.z());
			HGLOG_DEBUG("vertex( %f, %f, %f)",vec.x(), vec.y(), vec.z());
		}
		else if (basevecs->getType() == osg::Array::Vec3dArrayType)
		{
			const osg::Vec3d & vec = (*static_cast<const osg::Vec3dArray *>(basevecs))[vertexIndex];
			//vertex.Set(vec.x(), vec.y(), vec.z());
			HGLOG_DEBUG("vertex( %f, %f, %f)",vec.x(), vec.y(), vec.z());
		}
		else
		{
			OSG_NOTIFY(osg::FATAL) << "Vertex array is not Vec3 or Vec3d. Not implemented" << std::endl;
			throw "Vertex array is not Vec3 or Vec3d. Not implemented";
			//_succeeded = false;
			//return;
		}
		//mesh->SetControlPointAt(vertex, it->second);
		HGLOG_DEBUG("vertex( point %d )",it->second);


		const osg::Array * basenormals = pGeometry->getNormalArray();

		if (basenormals && basenormals->getNumElements()>0)
		{
			//FbxVector4 normal;
			if (basenormals->getType() == osg::Array::Vec3ArrayType)
			{
				const osg::Vec3  & vec = (*static_cast<const osg::Vec3Array  *>(basenormals))[normalIndex];
				//normal.Set(vec.x(), vec.y(), vec.z(), 0);
				HGLOG_DEBUG("normal( %f, %f, %f)",vec.x(), vec.y(), vec.z());
			}
			else if (basenormals->getType() == osg::Array::Vec3dArrayType)
			{
				const osg::Vec3d & vec = (*static_cast<const osg::Vec3dArray *>(basenormals))[normalIndex];
				//normal.Set(vec.x(), vec.y(), vec.z(), 0);
				HGLOG_DEBUG("normal( %f, %f, %f)",vec.x(), vec.y(), vec.z());
			}
			else
			{
				OSG_NOTIFY(osg::FATAL) << "Normal array is not Vec3 or Vec3d. Not implemented" << std::endl;
				throw "Normal array is not Vec3 or Vec3d. Not implemented";
				//_succeeded = false;
				//return;
			}
			HGLOG_DEBUG("normal( point %d )",it->second);

			//switch (pGeometry->getNormalBinding())
			//{
			//case osg::Geometry::BIND_PER_PRIMITIVE_SET:
			//case osg::Geometry::BIND_PER_PRIMITIVE:
			//case osg::Geometry::BIND_PER_VERTEX:
			//    break;
			//}
			//lLayerElementNormal->GetDirectArray().SetAt(it->second, normal);
		}

		if (texcoords)
		{
			const osg::Array * basetexcoords = pGeometry->getTexCoordArray(0);
			if (basetexcoords && basetexcoords->getNumElements()>0)
			{
				//FbxVector2 texcoord;
				if (basetexcoords->getType() == osg::Array::Vec2ArrayType)
				{
					const osg::Vec2 & vec = (*static_cast<const osg::Vec2Array *>(basetexcoords))[vertexIndex];
					//texcoord.Set(vec.x(), vec.y());
					HGLOG_DEBUG("uv( %f, %f)",vec.x(), vec.y());
				}
				else if (basetexcoords->getType() == osg::Array::Vec2dArrayType)
				{
					const osg::Vec2d & vec = (*static_cast<const osg::Vec2dArray *>(basetexcoords))[vertexIndex];
					//texcoord.Set(vec.x(), vec.y());
					HGLOG_DEBUG("uv( %f, %f)",vec.x(), vec.y());
				}
				else
				{
					OSG_NOTIFY(osg::FATAL) << "Texture coords array is not Vec2 or Vec2d. Not implemented" << std::endl;
					throw "Texture coords array is not Vec2 or Vec2d. Not implemented";
					//_succeeded = false;
					//return;
				}

				//lUVDiffuseLayer->GetDirectArray().SetAt(it->second, texcoord);
				HGLOG_DEBUG("uv( point %d )",it->second);
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
