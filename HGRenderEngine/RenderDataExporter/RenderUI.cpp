#include "StdAfx.h"
#include "RenderUI.h"

#include "hgcw\hgViewer\CompositeViewer.h"
#include "hgcw\hgViewer\SceneMgr.h"
#include "hg3d\BaseEntity.h"

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


#include "osg\StateSet"

#pragma comment(lib,"log4cpp.lib")
#pragma comment(lib,"HgLog.lib")

class SortSceneResourceVistor :public osg::NodeVisitor
{
public:
	SortSceneResourceVistor(hg3d::SceneMgr* sm,std::string code): _sm(sm),_code(code)
	{
		level = 0;
		//设置默认递归全部子节点
		setTraversalMode((TraversalMode)0xffffffff);
	}
	std::string _code;
	hg3d::SceneMgr* _sm;
	int level;

#define CHECK_IF_DO(class_type,point,function) \
	{ class_type* conv = dynamic_cast<class_type*>(point); 	if (conv) { \
	function \
	} }

	bool isGroup(osg::Node &node)
	{
		osg::Group* group = node.asGroup();
		return (group != nullptr);
	}
	
	//线型
	bool isLinerType(osg::Node& node)
	{
		CHECK_IF_DO(hg3d::HBar,&node,{ return true; });
		CHECK_IF_DO(hg3d::VBar,&node,{ return true; });
		CHECK_IF_DO(hg3d::ExtrudeMaterial,&node,{ return true; });
		CHECK_IF_DO(hg3d::LineMaterial,&node,{ return true; });
		return false;
	}

	//模型
	bool isModelType(osg::Node& node)
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

	//板件
	bool isPanel(osg::Node& node)
	{
		CHECK_IF_DO(hg3d::Panel,&node,{ return true; });
		return false;
	}

	//递归遍历所有子节点
	virtual void apply(osg::Node& node)
	{
		//如果是组
		if (isGroup(node))
		{
			debugGroup(*node.asGroup());
			processGroup(node);


			//路由到其他子节点
			osg::Group* group = node.asGroup();
			for (UINT i = 0; i < group->getNumChildren(); i++)
			{
				level++;
				osg::Node* pnode = (group->getChild(i));
				//traverse(*(node));
				apply(*pnode);
				level--;
			}
			return;
		}
		else
		{
			debugNode(node);
		}

		//如果是可以画的实体
		osg::Geode* geode = node.asGeode();
		if (geode)
		{
			for (UINT i = 0; i < geode->getNumDrawables() ; i++)
			{
				osg::Drawable* drawable = geode->getDrawable(i);
				if (!drawable) break;

				osg::Geometry* geometry = drawable->asGeometry();
				if (!geometry) break;


				if (drawable->getNumParents() > 1 || geometry->getNumParents() > 1)
				{
					HGLOG_DEBUG("drawable 重复");
				}

	
				//TODO: 加入mesh
				//获得顶点数量
				//获得面数量...........
				//获得顶点集合
				//获得法线集合
				//获得uv集合
				//获得三角面划分集合



				osg::Geometry::ArrayDataList& uvs = geometry->getTexCoordArrayList();	//拿uv
				HGLOG_DEBUG("uvs num:%d ",uvs.size());

				

				osg::Geometry::PrimitiveSetList& primitiveSet = geometry->getPrimitiveSetList();
				HGLOG_DEBUG("primitve num:%d ",primitiveSet.size());
				//primitiveSet.at(0)->asPrimitiveSet()-> //从里面拿osg用什么方式组织顶点集合的，譬如说 triangle 或者 polygon，顶点集合
				

				osg::Array* verts = geometry->getVertexArray();		//拿顶点集合
				if (verts)
				{HGLOG_DEBUG("verts num:%d ",verts->getNumElements());}

				osg::Array* colors = geometry->getColorArray();		//拿顶点着色
				if (colors) 
				{HGLOG_DEBUG("colors num:%d ",colors->getNumElements());}

				osg::Array* normals = geometry->getNormalArray();		//拿法线
				if (normals)
				{
					HGLOG_DEBUG("normal num:%d ",normals->getNumElements());
				}

				osg::IndexArray* indexArr = geometry->getVertexIndices();
				if (indexArr)
				{
					HGLOG_DEBUG("indexArr num:%d ",indexArr->getNumElements());
				}



				osg::StateSet* stateSet = geometry->getStateSet();
				if (stateSet)
				{
					osg::StateSet::TextureAttributeList& attrs = stateSet->getTextureAttributeList();
					osg::StateSet::ModeList& models = stateSet->getModeList();
					HGLOG_DEBUG("texture attrs:%d ",attrs.size());				
					HGLOG_DEBUG("texture models:%d ",models.size());	

// 					osg::StateAttribute* attr = floor->getOrCreateStateSet()->getTextureAttribute(0,StateAttribute::Type::TEXTURE);
// 					Texture2D* text2d = attr->asTexture();
// 					Image* image = text2d->getImage();
// 					image->getFileName();
				}

			}
			
		}
	}

	std::string processGroup(osg::Node &node)
	{
		if (isLinerType(node))
		{
			return ("liner");
		}
		else if (isModelType(node))
		{
			return("model");
		} 
		else if (isPanel(node))
		{
			return("panel");
		}
		else
		{
			return "other";
		}

	}

	void debugNode(osg::Node &node)
	{
		std::string libName = node.libraryName();
		std::string className = node.className();
		std::string nodeName = node.getName();
		HGLOG_DEBUG("libname: %s, level:%02d , classname: %s , nodename: %s ",libName.c_str(),level,className.c_str(),nodeName.c_str());
	}
	void debugGroup(osg::Group &node)
	{
		std::string libName = node.libraryName();
		std::string className = node.className();
		std::string nodeName = node.getName();
		int size = node.getNumChildren();
		HGLOG_DEBUG("libname: %s, level:%02d , classname: %s , nodename: %s child: %d type: %s "
				,libName.c_str(),level,className.c_str(),nodeName.c_str(),size,processGroup(node).c_str());
	}


};

#define TestConvert(class_type,point)	\
{	class_type* conv = dynamic_cast<class_type*>(point); \
	if (conv) {	HGLOG_DEBUG(#class_type" ok");	} \
}

void RenderUI::showRenderDlg()
{
	HgLog::HgLog::initDebugLogCategory();
	hg3d::SceneMgr* sm = hg3d::CompositeViewer::getSingleton()->getSceneMgr();
	
	//获得整个场景的根
	osg::Group* root = sm->get3DScene();
	
	//遍历整个场景
	SortSceneResourceVistor vistor(sm,"");
	root->accept(vistor);
	
	return;

	osg::Node *node00 = osgDB::readNodeFile( "E:\\XIANGMUSOFT\\TYBSOFT2016-back\\Ironware\\连接类\\层板托(衣柜)\\板拖.IVE" );
	if (node00)
	{
		HGLOG_DEBUG("load ok");
	}
	
	osg::Group* group01 = dynamic_cast<osg::Group*>(node00);
	if (group01)
	{
		HGLOG_DEBUG("group ok");
		for (int i = 0; i < group01->getNumChildren() ; i++)
		{
			osg::Node* child01 = group01->getChild(i);
			osg::Group* cgroup02 = dynamic_cast<osg::Group*>(child01);
			for (int j = 0; j < cgroup02->getNumChildren() ; j++)
			{
				osg::Node* cchild02 = cgroup02->getChild(i);
				osg::Group* ccgroup03 = dynamic_cast<osg::Group*>(cchild02);
				for (int k = 0; k < ccgroup03->getNumChildren() ; k++)
				{
					osg::Node* node = ccgroup03->getChild(i);
					TestConvert(osg::Drawable,node);
					TestConvert(osg::Group,node);
					TestConvert(osg::Geode,node);

					HGLOG_DEBUG("123");
				}

			}
		}
	}

}

