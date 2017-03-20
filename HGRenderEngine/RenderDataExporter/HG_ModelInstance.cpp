#include "StdAfx.h"
#include "HG_ModelInstance.h"
#include <stdexcept>

HG_ModelInstance::HG_ModelInstance(void)
{
	set_model_file("");
	set_mesh_to_world(HG_Mat());
}


HG_ModelInstance::HG_ModelInstance(std::string model_file,HG_Mat mesh_to_world)
{
	set_model_file(model_file);
	set_mesh_to_world(mesh_to_world);
}

HG_ModelInstance::~HG_ModelInstance(void)
{

}
