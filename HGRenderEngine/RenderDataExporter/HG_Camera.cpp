#include "StdAfx.h"
#include "HG_Camera.h"
#include <stdexcept>

HG_Camera::HG_Camera(void)
{
	set_fov(0.0);
	m_near_clip = 0.0;
	m_far_clip = 0.0;
	m_image_width = 0;
	m_image_height = 0;
	m_cubemap_render = false;
}


HG_Camera::~HG_Camera(void)
{
}



void HG_Camera::save(Json::Value& out)
{
	out["fov"] = get_fov();
	out["near_clip"] = get_near_clip();
	out["far_clip"] = get_far_clip();
	out["image_width"] = get_image_width();
	out["image_height"] = get_image_height();
	out["cubemap_render"] = get_cubemap_render();
	
	ref_view_to_world().save(out["view_to_world"]);
}

void HG_Camera::load(const Json::Value& in)
{
	set_fov(in["fov"].asFloat());
	set_near_clip(in["near_clip"].asFloat());
	set_far_clip(in["far_clip"].asFloat());
	set_image_width(in["image_width"].asUInt());
	set_image_height(in["image_height"].asUInt());
	set_cubemap_render(in["cubemap_render"].asBool());

	ref_view_to_world().load(in["view_to_world"]);
}

