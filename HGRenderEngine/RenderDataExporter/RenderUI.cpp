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
	
	//获得整个场景的根
	osg::Group* root = sm->get3DScene();
	
	//遍历整个场景
	HGSceneNodeVisitor vistor;
	//root->accept(vistor);
	HGLOG_DEBUG("scene ok");

	//osg::Node *node00 = osgDB::readNodeFile( "E:\\XIANGMUSOFT\\TYBSOFT2016-back\\Ironware\\连接类\\层板托(衣柜)\\板拖.IVE" );
	osg::Node *node00 = osgDB::readNodeFile( "D:\\123123123\\trian3.ive" );
	if (node00)
	{
		//node00->accept(vistor);
		HGLOG_DEBUG("load ok");
	}
	
	//定义输出json格式
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

