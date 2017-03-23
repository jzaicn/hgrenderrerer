#pragma once
#include "HG_BaseModel.h"

class HG_Exposure :public HG_BaseModel
{
public:
	HG_Exposure(void)
	{
		set_exposure_enable(true);
		set_exposure(0.0);
		set_high_light(0.0);
		set_half_tone(0.0);
		set_shadow(0.0);
		set_saturation(0.0);
		set_white_balance(0.0);
	}

	~HG_Exposure(void)
	{

	}

	HG_Exposure(const HG_Exposure& other)	
	{
		set_exposure_enable(other.get_exposure_enable());
		set_exposure(other.get_exposure());
		set_high_light(other.get_high_light());
		set_half_tone(other.get_half_tone());
		set_shadow(other.get_shadow());
		set_saturation(other.get_saturation());
		set_white_balance(other.get_white_balance());
	}

	HG_Exposure& operator=(const HG_Exposure &other)	
	{
		set_exposure_enable(other.get_exposure_enable());
		set_exposure(other.get_exposure());
		set_high_light(other.get_high_light());
		set_half_tone(other.get_half_tone());
		set_shadow(other.get_shadow());
		set_saturation(other.get_saturation());
		set_white_balance(other.get_white_balance());
		return *this;
	}



	virtual std::string get_classname() override
	{
		return "HG_Exposure";
	}

	virtual void save(Json::Value& out) override
	{
		out["exposure_enable"] = get_exposure_enable();
		out["exposure"] = get_exposure();
		out["high_light"] = get_high_light();
		out["half_tone"] = get_half_tone();
		out["shadow"] = get_shadow();
		out["saturation"] = get_saturation();
		out["white_balance"] = get_white_balance();
	}

	virtual void load(const Json::Value& in) override
	{
		set_exposure_enable(in["exposure_enable"].asBool());
		set_exposure(in["exposure"].asFloat());
		set_high_light(in["high_light"].asFloat());
		set_half_tone(in["half_tone"].asFloat());
		set_shadow(in["shadow"].asFloat());
		set_saturation(in["saturation"].asFloat());
		set_white_balance(in["white_balance"].asFloat());
	}

private:
	GETSET(bool,exposure_enable);
	GETSET(float,exposure);
	GETSET(float,high_light);
	GETSET(float,half_tone);
	GETSET(float,shadow);
	GETSET(float,saturation);
	GETSET(float,white_balance);

};

