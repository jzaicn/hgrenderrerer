#pragma once

#include "BaseModel.h"
class HG_MeshInstance
{
public:
	HG_MeshInstance(void);
	~HG_MeshInstance(void);


	void saveTo(_Out_ EH_MeshInstance& inst);
	void loadFrom(const EH_MeshInstance& inst);

private:
	

	EH_MeshInstance* create();

private:
	GETSET(EH_MeshInstance*,meshInstance);	

	GETSET(CString,mesh_name);/**< The name of the mesh which we reference to */
	GETSET_VECTYPE(EH_Mat,mesh_to_world);/**< Mesh local space to world space transform */
	GETSET(CString,mtl_name);/**< The name of the material which we reference to */
};

