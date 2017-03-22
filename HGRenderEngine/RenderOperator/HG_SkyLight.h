#pragma once
#include "HG_BaseModel.h"

class HG_SkyLight :public HG_BaseModel
{
public:
	HG_SkyLight(void)
	{
		set_sky_light_enable(true);
		set_sky_light_intensity(0.0);
		set_hdr("");
		set_hdr_rotate(0.0);
	}

	~HG_SkyLight(void)
	{

	}

	HG_SkyLight(const HG_SkyLight& other)	
	{
		set_sky_light_enable(other.get_sky_light_enable());
		set_sky_light_intensity(other.get_sky_light_intensity());
		set_hdr(other.get_hdr());
		set_hdr_rotate(other.get_hdr_rotate());
	}

	HG_SkyLight& operator=(const HG_SkyLight &other)	
	{
		set_sky_light_enable(other.get_sky_light_enable());
		set_sky_light_intensity(other.get_sky_light_intensity());
		set_hdr(other.get_hdr());
		set_hdr_rotate(other.get_hdr_rotate());
		return *this;
	}



	virtual std::string get_classname() override
	{
		return "HG_SkyLight";
	}

	virtual void save(Json::Value& out) override
	{
		out["sky_light_enable"] = get_sky_light_enable();
		out["sky_light_intensity"] = get_sky_light_intensity();
		out["hdr"] = get_hdr();
		out["hdr_rotate"] = get_hdr_rotate();
	}

	virtual void load(const Json::Value& in) override
	{
		set_sky_light_enable(in["sky_light_enable"].asBool());
		set_sky_light_intensity(in["sky_light_intensity"].asFloat());
		set_hdr(in["hdr"].asString());
		set_hdr_rotate(in["hdr_rotate"].asFloat());
	}

private:
	GETSET(bool,sky_light_enable);
	GETSET(float,sky_light_intensity);
	GETSET(std::string,hdr);
	GETSET(float,hdr_rotate);

};

