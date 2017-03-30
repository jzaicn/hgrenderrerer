#include "StdAfx.h"
#include "HG_ModelInstance.h"
#include <stdexcept>

HG_ModelInstance::HG_ModelInstance(void)
{
	set_unique_code("");
	set_model_file("");
	set_mesh_to_world(HG_Mat());
}


HG_ModelInstance::HG_ModelInstance(std::string model_file,HG_Mat mesh_to_world)
{
	set_unique_code(model_file);
	set_model_file(model_file);
	set_mesh_to_world(mesh_to_world);
}

HG_ModelInstance::~HG_ModelInstance(void)
{

}

std::string HG_ModelInstance::get_classname()
{
	return "HG_ModelInstance";
}

void HG_ModelInstance::save(Json::Value& out)
{
	out["model_file"] = get_model_file();
	out["unique_code"] = get_unique_code();
	ref_mesh_to_world().save(out["mesh_to_world"]);
}

void HG_ModelInstance::load(const Json::Value& in)
{
	set_model_file(in["model_file"].asString());
	set_unique_code(in["unique_code"].asString());
	ref_mesh_to_world().load(in["mesh_to_world"]);
}
