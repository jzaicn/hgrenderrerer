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
	osg::Node *node00 = osgDB::readNodeFile( "D:\\123123123\\trian2.ive" );
	if (node00)
	{
		//node00->accept(vistor);
		HGLOG_DEBUG("load ok");
	}
	
	Json::Value output;
	HG_SceneCenter mat;
	mat.addModelInstance(HG_ModelInstance("123123",HG_Mat()));

	mat.save(output);
	HGLOG_DEBUG(output.toStyledString().c_str());

	HG_Mat mat2;
	mat2.load(output);
	
// 	std::ofstream  writestream("d:\\1.txt");
// 	if (writestream.is_open())
// 	{
// 		writestream << root.toStyledString().c_str() ;
// 		writestream.flush();
// 		writestream.close();
// 	}
		
// 	std::ifstream  readstream("d:\\1.txt");
// 	if (readstream.is_open())
// 	{
// 		std::string text;
// 		readstream >> text ;
// 		readstream.close();
// 
// 		Json::Reader reader;
// 		Json::Value root;
// 		if (reader.parse(text,root))
// 		{
// 			HGLOG_DEBUG("json: %s",root.toStyledString().c_str());
// 		}
// 	}

	
}

