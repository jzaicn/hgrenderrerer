#pragma once

#include "HG_BaseModel.h"
class HG_MeshInstance :public HG_BaseModel
{
public:
	HG_MeshInstance(void);
	HG_MeshInstance(std::string mesh_code,std::string material_code,HG_Mat mesh_to_world);
	~HG_MeshInstance(void);

	HG_MeshInstance(const HG_MeshInstance& other)	
	{
		set_mesh_code(other.get_mesh_code());
		set_mesh_to_world(other.get_mesh_to_world());
		set_material_code(other.get_material_code());
		set_unique_code(other.get_unique_code());
	}
	
	HG_MeshInstance& operator=(const HG_MeshInstance &other)	
	{
		set_mesh_code(other.get_mesh_code());
		set_mesh_to_world(other.get_mesh_to_world());
		set_material_code(other.get_material_code());
		set_unique_code(other.get_unique_code());
		return *this;
	}

	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

private:
	GETSET(std::string,mesh_code);
	GETSET(HG_Mat,mesh_to_world);
	GETSET(std::string,material_code);
	GETSET(std::string,unique_code);
};

