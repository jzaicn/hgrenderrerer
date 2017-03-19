#include "StdAfx.h"
#include "HG_MeshInstance.h"
#include <stdexcept>

HG_MeshInstance::HG_MeshInstance(void)
{
	set_mesh_name("");
	clear_mesh_to_world();
	set_mtl_name("");

	set_meshInstance(create());
}


HG_MeshInstance::~HG_MeshInstance(void)
{
	if (get_meshInstance())
	{
		free(get_meshInstance());
		set_meshInstance(NULL);
	}
}

void HG_MeshInstance::saveTo(_Out_ EH_MeshInstance& inst)
{
	inst.mesh_name = get_mesh_name().GetBuffer();
	inst.mtl_name = get_mtl_name().GetBuffer();
	get_mesh_to_world(inst.mesh_to_world);
}

void HG_MeshInstance::loadFrom(const EH_MeshInstance& inst)
{
	set_mesh_name(inst.mesh_name);
	set_mtl_name(inst.mtl_name);
	set_mesh_to_world(inst.mesh_to_world);
}

EH_MeshInstance* HG_MeshInstance::create()
{
	EH_MeshInstance* val = (EH_MeshInstance*)(malloc(sizeof(EH_MeshInstance)));
	if (!val)
	{
		throw std::runtime_error("EH_MeshInstance ´´½¨Ê§°Ü");
	}
	saveTo(*val);
	return val;
}

