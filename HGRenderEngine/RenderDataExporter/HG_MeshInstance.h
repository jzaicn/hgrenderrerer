#pragma once

#include "HG_BaseModel.h"
class HG_MeshInstance :public HG_BaseModel
{
public:
	HG_MeshInstance(void);
	HG_MeshInstance(std::string mesh_code,std::string material_code,HG_Mat mesh_to_world);
	~HG_MeshInstance(void);

	std::string getUniqueCode(){ return "";};

private:
	GETSET(std::string,mesh_code);/**< The name of the mesh which we reference to */
	GETSET(HG_Mat,mesh_to_world);/**< Mesh local space to world space transform */
	GETSET(std::string,material_code);/**< The name of the material which we reference to */
	GETSET(std::string,unique_code);
};

