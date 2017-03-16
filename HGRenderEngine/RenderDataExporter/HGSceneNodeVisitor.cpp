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


HGSceneNodeVisitor::HGSceneNodeVisitor(void)
{
	m_level = 0;
	//����Ĭ�ϵݹ�ȫ���ӽڵ�
	setTraversalMode(osg::NodeVisitor::TraversalMode::TRAVERSE_ALL_CHILDREN);
	setTraversalMask(0xffffffff);
	setNodeMaskOverride(0);
	setVisitorType(osg::NodeVisitor::NODE_VISITOR);
}


HGSceneNodeVisitor::~HGSceneNodeVisitor(void)
{
}

bool HGSceneNodeVisitor::isGroup(osg::Node &node)
{
	osg::Group* group = node.asGroup();
	return (group != nullptr);
}

bool HGSceneNodeVisitor::isGeode(osg::Node &node)
{
	osg::Geode* geode = node.asGeode();
	return (geode != nullptr);
}

bool HGSceneNodeVisitor::isGroupLiner(osg::Node& node)
{
	CHECK_IF_DO(hg3d::HBar,&node,{ return true; });
	CHECK_IF_DO(hg3d::VBar,&node,{ return true; });
	CHECK_IF_DO(hg3d::ExtrudeMaterial,&node,{ return true; });
	CHECK_IF_DO(hg3d::LineMaterial,&node,{ return true; });
	return false;
}

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

bool HGSceneNodeVisitor::isGroupIgnore(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Borer,&node,{ return true; });
	CHECK_IF_DO(hg3d::BorerShow,&node,{ return true; });
	return false;
}

bool HGSceneNodeVisitor::isGroupPanel(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Panel,&node,{ return true; });
	return false;
}

void HGSceneNodeVisitor::apply(osg::Node& node)
{
	//�������
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

		//����ǿ��Ի���ʵ��
		if (isGeode(node))
		{
			osg::Geode* geode = node.asGeode();
			for (UINT i = 0; i < geode->getNumDrawables() ; i++)
			{
				osg::Drawable* drawable = geode->getDrawable(i);
				if (!drawable) break;

				osg::Geometry* geometry = drawable->asGeometry();
				if (!geometry) break;


				if (drawable->getNumParents() > 1 || geometry->getNumParents() > 1)
				{
					HGLOG_DEBUG("drawable �ظ�");
				}


				//TODO: ����mesh
				//��ö�������
				//���������...........
				//��ö��㼯��
				//��÷��߼���
				//���uv����
				//��������滮�ּ���
// 
// 				osg::Array* verts = geometry->getVertexArray();		//�ö��㼯��
// 				if (verts && verts->getNumElements() > 0 )
// 				{
// 					HGLOG_DEBUG("verts num:%d ",verts->getNumElements());
// 
// 					osg::Array* textCoors = geometry->getTexCoordArray();		//�ö�����ɫ
// 					if (textCoors) 
// 					{	
// 						HGLOG_DEBUG("textCoors num:%d ",textCoors->getNumElements());
// 						if (textCoors->getNumElements() == verts->getNumElements())
// 						{
// 							HGLOG_DEBUG("textCoors used ");
// 							//TODO: ����ǰ�ڵ�Ĳ���
// 
// 						}
// 					}
// 
// 					//TODO: ����mesh
// 				}
// 
// 
// 				osg::Geometry::ArrayDataList& uvs = geometry->getTexCoordArrayList();	//��uv
// 				HGLOG_DEBUG("uvs num:%d ",uvs.size());
// 
// 
// 
// 				osg::Geometry::PrimitiveSetList& primitiveSet = geometry->getPrimitiveSetList();
// 				HGLOG_DEBUG("primitve num:%d ",primitiveSet.size());
// 				//primitiveSet.at(0)->asPrimitiveSet()-> //��������osg��ʲô��ʽ��֯���㼯�ϵģ�Ʃ��˵ triangle ���� polygon�����㼯��
// 
// 
// 				osg::Array* verts = geometry->getVertexArray();		//�ö��㼯��
// 				if (verts)
// 				{HGLOG_DEBUG("verts num:%d ",verts->getNumElements());}
// 
// 				osg::Array* colors = geometry->getColorArray();		//�ö�����ɫ
// 				if (colors) 
// 				{HGLOG_DEBUG("colors num:%d ",colors->getNumElements());}
// 
// 				osg::Array* normals = geometry->getNormalArray();		//�÷���
// 				if (normals)
// 				{
// 					HGLOG_DEBUG("normal num:%d ",normals->getNumElements());
// 				}
// 
// 				osg::IndexArray* indexArr = geometry->getVertexIndices();
// 				if (indexArr)
// 				{
// 					HGLOG_DEBUG("indexArr num:%d ",indexArr->getNumElements());
// 				}
// 
// 
// 
// 				osg::StateSet* stateSet = geometry->getStateSet();
// 				if (stateSet)
// 				{
// 					osg::StateSet::TextureAttributeList& attrs = stateSet->getTextureAttributeList();
// 					osg::StateSet::ModeList& models = stateSet->getModeList();
// 					HGLOG_DEBUG("texture attrs:%d ",attrs.size());				
// 					HGLOG_DEBUG("texture models:%d ",models.size());	
// 
// 					// 					osg::StateAttribute* attr = floor->getOrCreateStateSet()->getTextureAttribute(0,StateAttribute::Type::TEXTURE);
// 					// 					Texture2D* text2d = attr->asTexture();
// 					// 					Image* image = text2d->getImage();
// 					// 					image->getFileName();
// 				}

			}

		}
	}
}

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

void HGSceneNodeVisitor::debugNode(osg::Node &node)
{
	std::string libName = node.libraryName();
	std::string className = node.className();
	std::string nodeName = node.getName();
	HGLOG_DEBUG("libname: %s, m_level:%02d , classname: %s , nodename: %s ",libName.c_str(),m_level,className.c_str(),nodeName.c_str());
}

void HGSceneNodeVisitor::debugGroup(osg::Group &node)
{
	std::string libName = node.libraryName();
	std::string className = node.className();
	std::string nodeName = node.getName();
	int size = node.getNumChildren();
	HGLOG_DEBUG("libname: %s, m_level:%02d , classname: %s , nodename: %s child: %d type: %s "
		,libName.c_str(),m_level,className.c_str(),nodeName.c_str(),size,getGroupFilterName(node).c_str());
}
