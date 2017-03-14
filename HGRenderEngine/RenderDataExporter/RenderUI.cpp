#include "StdAfx.h"
#include "RenderUI.h"

#include "hgcw\hgViewer\CompositeViewer.h"
#include "hgcw\hgViewer\SceneMgr.h"
#include "hg3d\BaseEntity.h"

#include "HgLog\HgLog.h"
#include "osg\Geode"
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



	//递归遍历所有子节点
	virtual void apply(osg::Node& node)
	{
		std::string libName = node.libraryName();
		std::string className = node.className();
		std::string nodeName = node.getName();
		HGLOG_DEBUG("libname: %s, level:%02d , classname: %s , nodename: %s ",libName.c_str(),level,className.c_str(),nodeName.c_str());
		if (className.compare("Group") == 0)
		{
			hg3d::BaseEntity* entity = dynamic_cast<hg3d::BaseEntity*>(&node);	
			if (entity)
			{
				HGLOG_DEBUG("------------------------------",libName.c_str(),className.c_str(),nodeName.c_str());
			}
		}

		//如果是组
		osg::Group* group = dynamic_cast<osg::Group*>(&node);
		if (group)
		{
			for (UINT i = 0; i < group->getNumChildren(); i++)
			{
				level++;
				traverse(*(group->getChild(i)));
				level--;
			}
			return;
		}

		//如果是可以画的实体
		osg::Geode* geode = dynamic_cast<osg::Geode*>(&node);
		if (geode)
		{
			for (UINT i = 0; i < geode->getNumDrawables() ; i++)
			{
				osg::Drawable* drawable = geode->getDrawable(i);
				if (drawable->getNumParents() > 1)
				{
					//TODO: 检查重复性
					//如果重复则跳过
					HGLOG_DEBUG("drawable 重复");
				}
				//TODO: 吧draw作为mesh插入队列
				osg::Geometry* geometry = drawable->asGeometry();
				if (geometry->getNumParents() > 1)
				{
					//TODO: 检查重复性
					HGLOG_DEBUG("geometory 重复");
				}
				//TODO: 加入mesh
				//获得顶点数量
				//获得面数量
				//获得顶点集合
				//获得法线集合
				//获得uv集合
				//获得三角面划分集合
				geometry->getVertexArray();
				

			}
			
		}
	}


};


void RenderUI::showRenderDlg()
{
	HgLog::HgLog::initDebugLogCategory();
	hg3d::SceneMgr* sm = hg3d::CompositeViewer::getSingleton()->getSceneMgr();
	
	//获得整个场景的根
	osg::Group* root = sm->get3DScene();
	
	//遍历整个场景
	SortSceneResourceVistor vistor(sm,"");
	root->accept(vistor);
	
}
