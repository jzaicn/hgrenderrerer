#pragma once

#include "HG_BaseModel.h"
class HG_ModelInstance :public HG_BaseModel
{
public:
	HG_ModelInstance(void);
	HG_ModelInstance(std::string model_file,HG_Mat mesh_to_world);
	~HG_ModelInstance(void);

private:
	GETSET(std::string,model_file);/**< The name of the mesh which we reference to */
	GETSET(HG_Mat,mesh_to_world);/**< Mesh local space to world space transform */
	GETSET(std::string,unique_code);
};

