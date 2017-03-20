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
