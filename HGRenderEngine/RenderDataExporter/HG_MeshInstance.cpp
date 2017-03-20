#include "StdAfx.h"
#include "HG_MeshInstance.h"
#include <stdexcept>

HG_MeshInstance::HG_MeshInstance(void)
{
	set_mesh_code("");
	set_material_code("");
	set_mesh_to_world(HG_Mat());
}


HG_MeshInstance::HG_MeshInstance(std::string mesh_code,std::string material_code,HG_Mat mesh_to_world)
{
	set_mesh_code(mesh_code);
	set_mesh_to_world(mesh_to_world);
	set_material_code(material_code);
}

HG_MeshInstance::~HG_MeshInstance(void)
{

}

std::string HG_MeshInstance::get_classname()
{
	return "HG_MeshInstance";
}

void HG_MeshInstance::save(Json::Value& out)
{
	out["mesh_code"] = get_mesh_code();
	out["material_code"] = get_material_code();
	out["unique_code"] = get_unique_code();
	ref_mesh_to_world().save(out["mesh_to_world"]);
}

void HG_MeshInstance::load(const Json::Value& in)
{
	set_mesh_code(in["mesh_code"].asString());
	set_material_code(in["material_code"].asString());
	set_unique_code(in["unique_code"].asString());
	ref_mesh_to_world().load(in["mesh_to_world"]);
}
