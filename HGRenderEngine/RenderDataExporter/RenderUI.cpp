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
		//����Ĭ�ϵݹ�ȫ���ӽڵ�
		setTraversalMode((TraversalMode)0xffffffff);
	}
	std::string _code;
	hg3d::SceneMgr* _sm;
	int level;



	//�ݹ���������ӽڵ�
	/*virtual*/ void applyA(osg::Node& node)
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

		//�������
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

		//����ǿ��Ի���ʵ��
		osg::Geode* geode = dynamic_cast<osg::Geode*>(&node);
		if (geode)
		{
			for (UINT i = 0; i < geode->getNumDrawables() ; i++)
			{
				osg::Drawable* drawable = geode->getDrawable(i);
				if (drawable->getNumParents() > 1)
				{
					//TODO: ����ظ���
					//����ظ�������
					HGLOG_DEBUG("drawable �ظ�");
				}
				//TODO: ��draw��Ϊmesh�������
				osg::Geometry* geometry = drawable->asGeometry();
				if (geometry->getNumParents() > 1)
				{
					//TODO: ����ظ���
					HGLOG_DEBUG("geometory �ظ�");
				}
				//TODO: ����mesh
				//��ö�������
				//���������
				//��ö��㼯��
				//��÷��߼���
				//���uv����
				//��������滮�ּ���
				geometry->getVertexArray();
				

			}
			
		}
	}



//	virtual void apply(osg::Node& node){HGLOG_DEBUG("Node");NodeVisitor::apply(node);};
	virtual void apply(osg::Geode& node)
	{
		std::string libName = node.libraryName();
		std::string className = node.className();
		std::string nodeName = node.getName();
		HGLOG_DEBUG("libname: %s, level:%02d , classname: %s , nodename: %s ",libName.c_str(),level,className.c_str(),nodeName.c_str());
	};
	virtual void apply(osg::Group& node)
	{
		HGLOG_DEBUG("Group");
		if (node)
		{
			for (UINT i = 0; i < node.getNumChildren(); i++)
			{
				level++;
				traverse(*(node.getChild(i)));
				level--;
			}
			return;
		}
	};
// 	virtual void apply(osg::Transform& node){HGLOG_DEBUG("Transform");NodeVisitor::apply(node);};
// 	virtual void apply(osg::MatrixTransform& node){HGLOG_DEBUG("MatrixTransform");NodeVisitor::apply(node);};
// 	virtual void apply(osg::PositionAttitudeTransform& node){HGLOG_DEBUG("PositionAttitudeTransform");NodeVisitor::apply(node);};
};


void RenderUI::showRenderDlg()
{
	HgLog::HgLog::initDebugLogCategory();
	hg3d::SceneMgr* sm = hg3d::CompositeViewer::getSingleton()->getSceneMgr();
	
	//������������ĸ�
	osg::Group* root = sm->get3DScene();
	
	//������������
	SortSceneResourceVistor vistor(sm,"");
	root->accept(vistor);
	
	HGLOG_DEBUG("-------------------------");
	osg::NodePath& path = vistor.getNodePath();
	for (int i = 0; i <  path.size(); i++)
	{
		std::string libName = path.at(i)->libraryName();
		std::string className = path.at(i)->className();
		std::string nodeName = path.at(i)->getName();
		HGLOG_DEBUG("libname: %s, level:%02d , classname: %s , nodename: %s ",libName.c_str(),99,className.c_str(),nodeName.c_str());
	}
}
