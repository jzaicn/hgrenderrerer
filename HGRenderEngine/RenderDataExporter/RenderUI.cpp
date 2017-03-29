#include "StdAfx.h"
#include "RenderUI.h"

#include "hgcw\hgViewer\CompositeViewer.h"
#include "hgcw\hgViewer\SceneMgr.h"
#include "hg3d\BaseEntity.h"
#include "HgLog\HgLog.h"
#include "HGSceneNodeVisitor.h"
#include "JsonCpp/json.h"
#include "osg\StateSet"
#include <fstream>
#include "HG_Light.h"


#define TestConvert(class_type,point)	\
{	class_type* conv = dynamic_cast<class_type*>(point); \
	if (conv) {	HGLOG_DEBUG(#class_type" ok");	} \
}





void RenderUI::save2file()
{
	//�������json��ʽ
	Json::Value output;
	HG_SceneCenter::inst().save(output);

	//���浽�ļ�,һ��json
	Json::FastWriter fastwriter;
	std::string result = fastwriter.write(output);
	//std::string result = output.toStyledString();
	std::ofstream  writestream("d:\\room.json");
	if (writestream.is_open())
	{
		writestream << result ;
		writestream.flush();
		writestream.close();
	}

	//չ����json
	std::ofstream  writestream2("d:\\room_open.json");
	if (writestream2.is_open())
	{
		writestream2 << output.toStyledString() ;
		writestream2.flush();
		writestream2.close();
	}
}


void RenderUI::showRenderDlg()
{
	HgLog::HgLog::initDebugLogCategory();
	HG_SceneCenter::inst().clear();


	
	//���ö�ȡ�ⲿiveģ��
#if 0	
	//osg::Node *node00 = osgDB::readNodeFile( "E:\\XIANGMUSOFT\\TYBSOFT2016-back\\Ironware\\������\\�����(�¹�)\\����.IVE" );
	osg::Node *node00 = osgDB::readNodeFile( "D:\\123123123\\trian3.ive" );
	if (node00)
	{
		HGSceneNodeVisitor vistor;
		node00->accept(vistor);
		HGLOG_DEBUG("load ok");
	}
#endif // 1
	
	

	//������������
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

	//���ö�ȡ�ⲿģ�ͣ������������
#if 0
// 	HG_ModelInstance model;
// 	model.set_unique_code("include_test_ess");
// 	model.set_model_file("D:\\default.ess");
// 	model.set_mesh_to_world(HG_Mat(
// 		HG_Vec4(1, 0, 0, 0),
// 		HG_Vec4(0, 1, 0, 0),
// 		HG_Vec4(0, 0, 1, 0),
// 		HG_Vec4(0, 0, 0, 1)
// 		));
// 	HG_SceneCenter::inst().addModelInstance(model);



#endif






	//���ö�ȡ�ⲿģ�ͣ������������
#if 0
	HG_ModelInstance model;
	model.set_unique_code("include_test_ess");
	model.set_model_file("D:\\default.ess");
	model.set_mesh_to_world(HG_Mat(
	 	HG_Vec4(1, 0, 0, 0),
	 	HG_Vec4(0, 1, 0, 0),
	 	HG_Vec4(0, 0, 1, 0),
	 	HG_Vec4(0, 0, 0, 1)
	 	));
	HG_SceneCenter::inst().addModelInstance(model);

	HG_ModelInstance model;
	model.set_unique_code("include_test_ess");
	model.set_model_file("D:\\default.ess");
	model.set_mesh_to_world(HG_Mat(
		HG_Vec4(1, 0, 0, 0),
		HG_Vec4(0, 1, 0, 0),
		HG_Vec4(0, 0, 1, 0),
		HG_Vec4(0, 0, 0, 1)
		));
	HG_SceneCenter::inst().addModelInstance(model);
	save2file();
#endif


	//���������ģ�ͼӲ��ģ��
#if 0
	//ok

	osg::Node *node00 = osgDB::readNodeFile( "D:\\trian.ive" );
	if (node00)
	{
		HGSceneNodeVisitor vistor;
		node00->accept(vistor);
		HGLOG_DEBUG("load ok");
	}

	HG_ModelInstance model;
	model.set_unique_code("include_test_ess");
	model.set_model_file("D:\\default.ess");
	model.set_mesh_to_world(HG_Mat(
		HG_Vec4(1, 0, 0, 0),
		HG_Vec4(0, 1, 0, 0),
		HG_Vec4(0, 0, 1, 0),
		HG_Vec4(0, 0, 0, 1)
		));
	HG_SceneCenter::inst().addModelInstance(model);

	HG_Camera camera;
	camera.set_view_to_world(HG_Mat(
		HG_Vec4(0.731353f, -0.681999f, -0.0f, 0.0f),
		HG_Vec4(0.255481f, 0.27397f, 0.927184f, 0.0f),
		HG_Vec4(-0.632338f, -0.678099f, 0.374607f, 0.0f),
		HG_Vec4(-38.681263f, -49.142731f, 21.895681f, 1.0f)
		)
		);
	camera.set_fov(45.0f);
	camera.set_near_clip(0.01f);
	camera.set_far_clip(1000.0f);
	camera.set_image_width(640);
	camera.set_image_height(480);
	HG_SceneCenter::inst().addCamera(camera);

	save2file();

#endif

	//TODO: ��������ģ�ͱ���������max�����������������Ч����100W����ǰ������
	//TODO: ���������������ű���
	//TODO: ������չ�
	//���������ģ�� ���Ӳ��ģ�� �� �ӵƹ�
#if 1
	//ok

// 	osg::Node *node00 = osgDB::readNodeFile( "D:\\trian3.ive" );
// 	if (node00)
// 	{
// 		HGSceneNodeVisitor vistor;
// 		node00->accept(vistor);
// 		HGLOG_DEBUG("load ok");
// 	}

	HG_ModelInstance model;
	model.set_unique_code("include_test_ess");
	model.set_model_file("D:\\hlightpad.ess");
	model.set_mesh_to_world(HG_Mat(
		HG_Vec4(72.393044,0.0,0.0,0.0),
		HG_Vec4(0.0,72.393044,0.0,0.0),
		HG_Vec4(0.0,0.0,7.900704,0.0),
		HG_Vec4(-0.887037,-3.9764,-188.070313,1.0)
		));
	HG_SceneCenter::inst().addModelInstance(model);

	HG_Camera camera;
	camera.set_view_to_world(HG_Mat(
		HG_Vec4(-0.636078,-0.771625,-0.0,0.0),
		HG_Vec4(0.586748,-0.483678,0.649448,0.0),
		HG_Vec4(-0.50113,0.4131,0.760406,0.0),
		HG_Vec4(-5196.911621,3183.984131,7388.293457,1.0)
		)
		);
	camera.set_fov(45.0f);
	camera.set_near_clip(0.01f);
	camera.set_far_clip(1000.0f);
	camera.set_image_width(640);
	camera.set_image_height(480);
	HG_SceneCenter::inst().addCamera(camera);

	save2file();

#endif

	//�������ģ��
#if 0
	hg3d::SceneMgr* sm = hg3d::CompositeViewer::getSingleton()->getSceneMgr();

	//������������
	HGSceneNodeVisitor vistor;

	//������������ĸ�
	osg::Group* root = sm->get3DScene();
	root->accept(vistor);
	HGLOG_DEBUG("scene ok");

	osg::Camera* cam = sm->getHUD();
	osg::Matrix camMatrix = cam->getViewMatrix();
	HG_Mat worldMatrix = HG_Mat(
// 		HG_Vec4(camMatrix(0,0),camMatrix(0,1),camMatrix(0,2),camMatrix(0,3)),
// 		HG_Vec4(camMatrix(1,0),camMatrix(1,1),camMatrix(1,2),camMatrix(1,3)),
// 		HG_Vec4(camMatrix(2,0),camMatrix(2,1),camMatrix(2,2),camMatrix(2,3)),
// 		HG_Vec4(camMatrix(3,0),camMatrix(3,1),camMatrix(3,2),camMatrix(3,3))
HG_Vec4(-0.636078,-0.771625,-0.0,0.0),
HG_Vec4(0.586748,-0.483678,0.649448,0.0),
HG_Vec4(-0.50113,0.4131,0.760406,0.0),
HG_Vec4(-5196.911621,3183.984131,7388.293457,1.0)
		);
	HG_Camera camera;
	camera.set_view_to_world(worldMatrix);
	camera.set_fov(45.0f);
	camera.set_near_clip(0.01f);
	camera.set_far_clip(1000.0f);
	camera.set_image_width(640);
	camera.set_image_height(480);
	HG_SceneCenter::inst().addCamera(camera);
	

	save2file();
#endif

}

