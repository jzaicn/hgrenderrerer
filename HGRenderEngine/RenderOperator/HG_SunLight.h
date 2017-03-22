#pragma once
#include "HG_BaseModel.h"

class HG_SunLight :public HG_BaseModel
{
public:
	HG_SunLight(void)
	{
		set_sun_enable(true);
		set_sun_light_intensity(0.0);
		set_sun_color(0);
		set_soft_shadow(0.0);
		set_sun_angle(0.0);
		set_sun_height(0.0);
	}

	~HG_SunLight(void)
	{

	}

	HG_SunLight(const HG_SunLight& other)	
	{
		set_sun_enable(other.get_sun_enable());
		set_sun_light_intensity(other.get_sun_light_intensity());
		set_sun_color(other.get_sun_color());
		set_soft_shadow(other.get_soft_shadow());
		set_sun_angle(other.get_sun_angle());
		set_sun_height(other.get_sun_height());
	}

	HG_SunLight& operator=(const HG_SunLight &other)	
	{
		set_sun_enable(other.get_sun_enable());
		set_sun_light_intensity(other.get_sun_light_intensity());
		set_sun_color(other.get_sun_color());
		set_soft_shadow(other.get_soft_shadow());
		set_sun_angle(other.get_sun_angle());
		set_sun_height(other.get_sun_height());
		return *this;
	}



	virtual std::string get_classname() override
	{
		return "HG_SunLight";
	}

	virtual void save(Json::Value& out) override
	{
		out["sun_enable"] = get_sun_enable();
		out["sun_light_intensity"] = get_sun_light_intensity();
		out["sun_color"] = get_sun_color();
		out["soft_shadow"] = get_soft_shadow();
		out["sun_angle"] = get_sun_angle();
		out["sun_height"] = get_sun_height();
	}

	virtual void load(const Json::Value& in) override
	{
		set_sun_enable(in["sun_enable"].asBool());
		set_sun_light_intensity(in["sun_light_intensity"].asFloat());
		set_sun_color(in["sun_color"].asUInt());
		set_soft_shadow(in["soft_shadow"].asFloat());
		set_sun_angle(in["sun_angle"].asFloat());
		set_sun_height(in["sun_height"].asFloat());
	}

private:
	GETSET(bool,sun_enable);
	GETSET(float,sun_light_intensity);
	GETSET(UINT,sun_color);
	GETSET(float,soft_shadow);
	GETSET(float,sun_angle);
	GETSET(float,sun_height);

};

