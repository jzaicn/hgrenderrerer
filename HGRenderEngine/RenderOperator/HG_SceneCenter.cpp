#include "StdAfx.h"
#include "HG_SceneCenter.h"

HG_SceneCenter HG_SceneCenter::m_inst;

HG_SceneCenter::HG_SceneCenter(void)
{
}


HG_SceneCenter::~HG_SceneCenter(void)
{
}

std::string HG_SceneCenter::get_classname()
{
	return "HG_SceneCenter";
}


void HG_SceneCenter::save(Json::Value& out)
{
	JsonVectorSave(HG_Camera,cameraList);
	JsonVectorSave(HG_Light,lightList);
	JsonVectorSave(HG_Mesh,meshList);
	JsonVectorSave(HG_ModelInstance,modelList);
	JsonVectorSave(HG_Material,materialList);
	JsonVectorSave(HG_MeshInstance,meshInstanceList);
	JsonVectorSave(HG_SunLight,sun);
	JsonVectorSave(HG_SkyLight,sky);
	ref_exposure().save(out["exposure"]);
	ref_param().save(out["param"]);
}



void HG_SceneCenter::load(const Json::Value& in)
{
	JsonVectorLoad(HG_Camera,cameraList);
	JsonVectorLoad(HG_Light,lightList);
	JsonVectorLoad(HG_Mesh,meshList);
	JsonVectorLoad(HG_ModelInstance,modelList);
	JsonVectorLoad(HG_Material,materialList);
	JsonVectorLoad(HG_MeshInstance,meshInstanceList);
	JsonVectorLoad(HG_SunLight,sun);
	JsonVectorLoad(HG_SkyLight,sky);
	ref_param().load(in["param"]);
	ref_exposure().load(in["exposure"]);
}


