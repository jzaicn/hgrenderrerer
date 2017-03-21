#include "StdAfx.h"
#include "HG_Material.h"
#include <stdexcept>

HG_Material::HG_Material(void)
{
	set_type(color);
	set_image("");
	set_color(HG_Vec4(1.0,1.0,1.0,1.0));
}


HG_Material::~HG_Material(void)
{
}

std::string HG_Material::get_classname()
{
	return "HG_Material";
}

void HG_Material::save(Json::Value& out)
{
	out["type"] = (UINT)get_type();
	out["image"] = get_image();
	out["unique_code"] = get_unique_code();
	ref_color().save(out["color"]);

}

void HG_Material::load(const Json::Value& in)
{
	set_type((MType)in["type"].asUInt());
	set_image(in["image"].asString());
	set_unique_code(in["unique_code"].asString());
	ref_color().load(in["color"]);
}
