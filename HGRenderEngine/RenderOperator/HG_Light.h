#pragma once
#include "HG_BaseModel.h"

class HG_Light :public HG_BaseModel
{
public:
	HG_Light(void);
	~HG_Light(void);
	HG_Light(const HG_Light& other)	
	{
		set_type(other.get_type());
		set_ies_filename(other.get_ies_filename());
		set_intensity(other.get_intensity());
		set_size(other.get_size());
		set_light_to_world(other.get_light_to_world());
		set_unique_code(other.get_unique_code());
	}

	HG_Light& operator=(const HG_Light &other)	
	{
		set_type(other.get_type());
		set_ies_filename(other.get_ies_filename());
		set_intensity(other.get_intensity());
		set_size(other.get_size());
		set_light_to_world(other.get_light_to_world());
		set_unique_code(other.get_unique_code());
		return *this;
	}

	typedef enum {
		spot_light,
		point_light,
		flat_light,
	}LightType;


	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

private:
	
	GETSET(LightType,type);
	GETSET(std::string,ies_filename);	
	GETSET(float,intensity);
	GETSET(HG_Vec2,size);		
	GETSET(HG_Mat,light_to_world);		
	GETSET(std::string,unique_code);	


};

