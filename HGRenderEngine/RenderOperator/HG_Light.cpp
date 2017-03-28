#include "StdAfx.h"
#include "HG_Light.h"
#include <stdexcept>

HG_Light::HG_Light(void)
{
	set_unique_code("");
	set_type(spot_light);
	set_ies_filename("");
	set_intensity(0);
	set_size(HG_Vec2(0,0));
	set_light_to_world(HG_Mat());
}


HG_Light::~HG_Light(void)
{
	
}

std::string HG_Light::get_classname()
{
	return "HG_Light";
}

void HG_Light::save(Json::Value& out)
{
	out["type"] = get_type();
	out["ies_filename"] = get_ies_filename();
	out["intensity"] = get_intensity();
	out["unique_code"] = get_unique_code();
	ref_size().save(out["size"]);
	ref_light_to_world().save(out["light_to_world"]);
}

void HG_Light::load(const Json::Value& in)
{
	set_type((LightType)in["type"].asUInt());
	set_ies_filename(in["ies_filename"].asString());
	set_intensity(in["intensity"].asFloat());
	set_unique_code(in["unique_code"].asString());
	ref_size().load(in["size"]);
	ref_light_to_world().load(in["light_to_world"]);
}

