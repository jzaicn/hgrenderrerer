#include "StdAfx.h"
#include "HGSceneNodeVisitor.h"


#include "HgLog\HgLog.h"
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

#include "MeshProcer.h"

HGSceneNodeVisitor::HGSceneNodeVisitor(void)
{
	m_level = 0;
	//设置默认递归全部子节点
	setTraversalMode(osg::NodeVisitor::TraversalMode::TRAVERSE_ALL_CHILDREN);
	setTraversalMask(0xffffffff);
	setNodeMaskOverride(0);
	setVisitorType(osg::NodeVisitor::NODE_VISITOR);

	_succeedLastApply = true;
	_currentStateSet = new osg::StateSet();
}


HGSceneNodeVisitor::~HGSceneNodeVisitor(void)
{
}
//////////////////////////////////////////////////////////////////////////
// 类型检测
#if 1
//判断节点是否Group节点
bool HGSceneNodeVisitor::isGroup(osg::Node &node)
{
	osg::Group* group = node.asGroup();
	return (group != nullptr);
}

//判断节点是否用于绘图
bool HGSceneNodeVisitor::isGeode(osg::Node &node)
{
	osg::Geode* geode = node.asGeode();
	return (geode != nullptr);
}

//判断线型
bool HGSceneNodeVisitor::isGroupLiner(osg::Node& node)
{
	CHECK_IF_DO(hg3d::HBar,&node,{ return true; });
	CHECK_IF_DO(hg3d::VBar,&node,{ return true; });
	CHECK_IF_DO(hg3d::ExtrudeMaterial,&node,{ return true; });
	CHECK_IF_DO(hg3d::LineMaterial,&node,{ return true; });
	return false;
}

//判断模型
bool HGSceneNodeVisitor::isGroupModel(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Borer,&node,{ return true; });
	CHECK_IF_DO(hg3d::BorerShow,&node,{ return true; });
	CHECK_IF_DO(hg3d::Entity,&node,{ return true; });
	CHECK_IF_DO(hg3d::Girder,&node,{ return true; });
	CHECK_IF_DO(hg3d::Door,&node,{ return true; });
	CHECK_IF_DO(hg3d::AlumStrip,&node,{ return true; });
	CHECK_IF_DO(hg3d::Glass,&node,{ return true; });
	CHECK_IF_DO(hg3d::Model,&node,{ return true; });
	CHECK_IF_DO(hg3d::Shape,&node,{ return true; });
	CHECK_IF_DO(hg3d::NDoorCore,&node,{ return true; });
	CHECK_IF_DO(hg3d::NDoorFrame,&node,{ return true; });
	CHECK_IF_DO(hg3d::NDoorPocket,&node,{ return true; });
	CHECK_IF_DO(hg3d::DoorWindow,&node,{ return true; });
	CHECK_IF_DO(hg3d::SliderDoor,&node,{ return true; });
	return false;
}

//判断是否跳过这个节点
bool HGSceneNodeVisitor::isGroupIgnore(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Borer,&node,{ return true; });
	CHECK_IF_DO(hg3d::BorerShow,&node,{ return true; });
	return false;
}

//判断是否板件
bool HGSceneNodeVisitor::isGroupPanel(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Panel,&node,{ return true; });
	return false;
}
#endif
//////////////////////////////////////////////////////////////////////////
// 处理节点
#if 1























void HGSceneNodeVisitor::pushStateSet(const osg::StateSet* ss)
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


void HGSceneNodeVisitor::popStateSet(const osg::StateSet* ss)
{
	if (ss)
	{
		// restore the previous stateset
		_currentStateSet = _stateSetStack.top();
		_stateSetStack.pop();
	}
}

int HGSceneNodeVisitor::getMaterialIndex(const osg::StateSet* ss)
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


void HGSceneNodeVisitor::createListTriangle(const osg::Geometry* geo,
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


void HGSceneNodeVisitor::buildFaces(const osg::Geode& geo,
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

void HGSceneNodeVisitor::setControlPointAndNormalsAndUV(const osg::Geode& geo,
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

void HGSceneNodeVisitor::addPolygon(/*FbxMesh * mesh,*/ MapIndices & index_vert, const Triangle & tri, unsigned int drawableNum)
{
	addPolygont3(index_vert, tri.t1, tri.normalIndex1, drawableNum);
	addPolygont3(index_vert, tri.t2, tri.normalIndex2, drawableNum);
	addPolygont3(index_vert, tri.t3, tri.normalIndex3, drawableNum);

// 	mesh->AddPolygon(addPolygon(index_vert, tri.t1, tri.normalIndex1, drawableNum));
// 	mesh->AddPolygon(addPolygon(index_vert, tri.t2, tri.normalIndex2, drawableNum));
// 	mesh->AddPolygon(addPolygon(index_vert, tri.t3, tri.normalIndex3, drawableNum));
}

unsigned int HGSceneNodeVisitor::addPolygont3(MapIndices & index_vert, unsigned int vertIndex, unsigned int normIndex, unsigned int drawableNum)
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

void HGSceneNodeVisitor::ProcessGeode(osg::Geode* geode)
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

//递归遍历所有子节点
void HGSceneNodeVisitor::apply(osg::Node& node)
{
	//如果是组
	if (isGroup(node))
	{
		debugGroup(*node.asGroup());

		//if (isGroupIgnore(node)) return;
		//if (isGroupLiner(node)) ;
		//if (isGroupModel(node)) ;
		//if (isGroupPanel(node)) ;
		//else 
		groupRoute(node);

		return;
	}
	else
	{
		debugNode(node);

		//如果是可以画的实体
		if (isGeode(node))
		{
			osg::Geode* geode = node.asGeode();
			ProcessGeode(geode);

		}
	}
}


//路由子节点
void HGSceneNodeVisitor::groupRoute(osg::Node &node)
{
	osg::Group* group = node.asGroup();
	for (UINT i = 0; i < group->getNumChildren(); i++)
	{
		m_level++;
		osg::Node* pnode = (group->getChild(i));
		//traverse(*(node));
		apply(*pnode);
		m_level--;
	}
}

//识别节点的类型分类
std::string HGSceneNodeVisitor::getGroupFilterName(osg::Node &node)
{
	if (isGroupLiner(node))
	{
		return ("liner");
	}
	else if (isGroupModel(node))
	{
		return("model");
	} 
	else if (isGroupPanel(node))
	{
		return("panel");
	}
	else
	{
		return "other";
	}
}
#endif
//////////////////////////////////////////////////////////////////////////
// 调试输出
#if 1
//输出当前子节点
void HGSceneNodeVisitor::debugNode(osg::Node &node)
{
	std::string libName = node.libraryName();
	std::string className = node.className();
	std::string nodeName = node.getName();
	HGLOG_DEBUG("libname: %s, m_level:%02d , classname: %s , nodename: %s ",libName.c_str(),m_level,className.c_str(),nodeName.c_str());
}

//输出当前组节点
void HGSceneNodeVisitor::debugGroup(osg::Group &node)
{
	std::string libName = node.libraryName();
	std::string className = node.className();
	std::string nodeName = node.getName();
	int size = node.getNumChildren();
	HGLOG_DEBUG("libname: %s, m_level:%02d , classname: %s , nodename: %s child: %d type: %s "
		,libName.c_str(),m_level,className.c_str(),nodeName.c_str(),size,getGroupFilterName(node).c_str());
}
#endif