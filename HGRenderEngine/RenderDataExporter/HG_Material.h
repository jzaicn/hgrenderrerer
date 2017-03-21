#pragma once
#include "HG_BaseModel.h"

class HG_Material :public HG_BaseModel
{
public:
	HG_Material(void);
	~HG_Material(void);

	typedef enum{
		empty,
		image,
		color
	}MType;

	HG_Material(const HG_Material& other)	
	{
		set_type(other.get_type());
		set_image(other.get_image());
		set_unique_code(other.get_unique_code());
		set_color(other.get_color());
	}

	HG_Material& operator=(const HG_Material &other)	
	{
		set_type(other.get_type());
		set_image(other.get_image());
		set_unique_code(other.get_unique_code());
		set_color(other.get_color());
		return *this;
	}

	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

private:

	GETSET(MType,type);
	GETSET(std::string,image);
	GETSET(std::string,unique_code);
	GETSET(HG_Vec4,color);
};

