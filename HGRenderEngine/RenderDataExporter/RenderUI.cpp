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
	
	//设置读取整个场景
#if 0
	//遍历整个场景
	HGSceneNodeVisitor vistor;
	//root->accept(vistor);
	HGLOG_DEBUG("scene ok");
#endif // 0

	//设置读取外部ive模型
#if 1	
	//osg::Node *node00 = osgDB::readNodeFile( "E:\\XIANGMUSOFT\\TYBSOFT2016-back\\Ironware\\连接类\\层板托(衣柜)\\板拖.IVE" );
	osg::Node *node00 = osgDB::readNodeFile( "D:\\123123123\\trian3.ive" );
	if (node00)
	{
		HGSceneNodeVisitor vistor;
		node00->accept(vistor);
		HGLOG_DEBUG("load ok");
	}
#endif // 1
	
	

	//获得摄像机坐标
#if 0
	osg::Camera* cam = sm->getHUD();
	osg::Matrix camMatrix = cam->getViewMatrix();
	HG_Mat worldMatrix = HG_Mat(
		HG_Vec4(camMatrix(0,0),camMatrix(0,1),camMatrix(0,2),camMatrix(0,3)),
		HG_Vec4(camMatrix(1,0),camMatrix(1,1),camMatrix(1,2),camMatrix(1,3)),
		HG_Vec4(camMatrix(2,0),camMatrix(2,1),camMatrix(2,2),camMatrix(2,3)),
		HG_Vec4(camMatrix(3,0),camMatrix(3,1),camMatrix(3,2),camMatrix(3,3))
	);
	HG_Camera camera;
	camera.set_view_to_world(worldMatrix);
#endif

	//设置读取外部模型，并设置摄像机
#if 0
	HG_SceneCenter::inst().addModelInstance(HG_ModelInstance("D:\\picture.ess",HG_Mat()));
	HG_Camera camera;
	camera.set_view_to_world(
		HG_Mat(
			HG_Vec4( -0.957354    , 0.288917      ,-0.0            ,0.0 ), 
			HG_Vec4( -0.103087    ,-0.341588      , 0.934179       ,0.0 ), 
			HG_Vec4(  0.2699      , 0.89434       , 0.356804       ,0.0 ), 
			HG_Vec4( -53.738983   , 1015.807617   , 780.762573     ,1.0 )
		)
	);
	camera.set_cubemap_render(false);
	camera.set_far_clip(1000.0);
	camera.set_near_clip(0.0);
	HG_SceneCenter::inst().addCamera(camera);
#endif



	//定义输出json格式
	Json::Value output;
	HG_SceneCenter::inst().save(output);
	

	//保存到文件
#if 1
	Json::FastWriter fastwriter;
	//std::string result = fastwriter.write(output);
	std::string result = output.toStyledString();
	std::ofstream  writestream("d:\\room.json");
	if (writestream.is_open())
	{
		writestream << result ;
		writestream.flush();
		writestream.close();
	}
#else
	//打印成字符串
	HGLOG_DEBUG(output.toStyledString());
#endif
	
}

