#include "StdAfx.h"
#include "RenderUI.h"

#include "hgcw\hgViewer\CompositeViewer.h"
#include "hgcw\hgViewer\SceneMgr.h"
#include "hg3d\BaseEntity.h"
#include "HgLog\HgLog.h"
#include "HGSceneNodeVisitor.h"

#include "osg\StateSet"
#include <fstream>

#pragma comment(lib,"log4cpp.lib")
#pragma comment(lib,"HgLog.lib")


#define TestConvert(class_type,point)	\
{	class_type* conv = dynamic_cast<class_type*>(point); \
	if (conv) {	HGLOG_DEBUG(#class_type" ok");	} \
}

#include "JsonCpp/json.h"


void RenderUI::showRenderDlg()
{
	HgLog::HgLog::initDebugLogCategory();
	hg3d::SceneMgr* sm = hg3d::CompositeViewer::getSingleton()->getSceneMgr();
	
	//������������ĸ�
	osg::Group* root = sm->get3DScene();
	
	//������������
	HGSceneNodeVisitor vistor;
	//root->accept(vistor);
	HGLOG_DEBUG("scene ok");

	//osg::Node *node00 = osgDB::readNodeFile( "E:\\XIANGMUSOFT\\TYBSOFT2016-back\\Ironware\\������\\�����(�¹�)\\����.IVE" );
	osg::Node *node00 = osgDB::readNodeFile( "D:\\123123123\\trian3.ive" );
	if (node00)
	{
		//node00->accept(vistor);
		HGLOG_DEBUG("load ok");
	}
	
	//�������json��ʽ
	Json::Value output;

	HG_SceneCenter::inst().addModelInstance(HG_ModelInstance("E:\\HGRENDER\\Elara_SDK_1_0_76\\bin\\default.ess",HG_Mat()));
	HG_SceneCenter::inst().addCamera(HG_Camera());
	HG_SceneCenter::inst().save(output);
	


	Json::FastWriter fastwriter;
	std::string result = fastwriter.write(output);
	std::ofstream  writestream("d:\\room.json");
	if (writestream.is_open())
	{
		writestream << result ;
		writestream.flush();
		writestream.close();
	}
	
}

