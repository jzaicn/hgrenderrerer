#include "StdAfx.h"
#include "RenderUI.h"

#include "hgcw\hgViewer\CompositeViewer.h"
#include "hgcw\hgViewer\SceneMgr.h"
#include "hg3d\BaseEntity.h"
#include "HgLog\HgLog.h"
#include "HGSceneNodeVisitor.h"

#include "osg\StateSet"

#pragma comment(lib,"log4cpp.lib")
#pragma comment(lib,"HgLog.lib")


#define TestConvert(class_type,point)	\
{	class_type* conv = dynamic_cast<class_type*>(point); \
	if (conv) {	HGLOG_DEBUG(#class_type" ok");	} \
}

void RenderUI::showRenderDlg()
{
	HgLog::HgLog::initDebugLogCategory();
	hg3d::SceneMgr* sm = hg3d::CompositeViewer::getSingleton()->getSceneMgr();
	
	//������������ĸ�
	osg::Group* root = sm->get3DScene();
	
	//������������
	HGSceneNodeVisitor vistor;
	root->accept(vistor);
	
	return;

	osg::Node *node00 = osgDB::readNodeFile( "E:\\XIANGMUSOFT\\TYBSOFT2016-back\\Ironware\\������\\�����(�¹�)\\����.IVE" );
	if (node00)
	{
		HGLOG_DEBUG("load ok");
	}
// 	
// 	osg::Group* group01 = dynamic_cast<osg::Group*>(node00);
// 	if (group01)
// 	{
// 		HGLOG_DEBUG("group ok");
// 		for (int i = 0; i < group01->getNumChildren() ; i++)
// 		{
// 			osg::Node* child01 = group01->getChild(i);
// 			osg::Group* cgroup02 = dynamic_cast<osg::Group*>(child01);
// 			for (int j = 0; j < cgroup02->getNumChildren() ; j++)
// 			{
// 				osg::Node* cchild02 = cgroup02->getChild(i);
// 				osg::Group* ccgroup03 = dynamic_cast<osg::Group*>(cchild02);
// 				for (int k = 0; k < ccgroup03->getNumChildren() ; k++)
// 				{
// 					osg::Node* node = ccgroup03->getChild(i);
// 					TestConvert(osg::Drawable,node);
// 					TestConvert(osg::Group,node);
// 					TestConvert(osg::Geode,node);
// 
// 					HGLOG_DEBUG("123");
// 				}
// 
// 			}
// 		}
// 	}

}

