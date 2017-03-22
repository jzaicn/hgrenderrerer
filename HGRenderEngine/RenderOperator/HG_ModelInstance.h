#pragma once

#include "HG_BaseModel.h"
class HG_ModelInstance :public HG_BaseModel
{
public:
	HG_ModelInstance(void);
	HG_ModelInstance(std::string model_file,HG_Mat mesh_to_world);
	~HG_ModelInstance(void);

	HG_ModelInstance(const HG_ModelInstance& other)	
	{
		set_model_file(other.get_model_file());
		set_mesh_to_world(other.get_mesh_to_world());
		set_unique_code(other.get_unique_code());
	}

	HG_ModelInstance& operator=(const HG_ModelInstance &other)	
	{
		set_model_file(other.get_model_file());
		set_mesh_to_world(other.get_mesh_to_world());
		set_unique_code(other.get_unique_code());
		return *this;
	}

	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

private:
	GETSET(std::string,model_file);
	GETSET(HG_Mat,mesh_to_world);
	GETSET(std::string,unique_code);
};

