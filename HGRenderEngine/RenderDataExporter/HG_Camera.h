#pragma once
#include "HG_BaseModel.h"
class HG_Camera :public HG_BaseModel
{
public:
	HG_Camera(void);
	~HG_Camera(void);
	HG_Camera(const HG_Camera& other)
	{
		set_fov(other.get_fov());
		set_near_clip(other.get_near_clip());
		set_far_clip(other.get_far_clip());
		set_image_width(other.get_image_width());
		set_image_height(other.get_image_height());
		set_cubemap_render(other.get_cubemap_render());

		set_view_to_world(other.get_view_to_world());
	}

	virtual std::string get_classname() { return "HG_Camera"; };
	virtual void save(Json::Value& out) override;
	virtual void load(const Json::Value& in) override;


	HG_Camera& operator =(const HG_Camera &other) 
	{
		set_near_clip(other.get_near_clip());
		set_far_clip(other.get_far_clip());
		set_image_width(other.get_image_width());
		set_image_height(other.get_image_height());
		set_cubemap_render(other.get_cubemap_render());

		set_view_to_world(other.get_view_to_world());
	}

private:

	GETSET(float,fov);
	GETSET(float,near_clip);
	GETSET(float,far_clip);
	GETSET(UINT,image_width);
	GETSET(UINT,image_height);
	GETSET(bool,cubemap_render);

	GETSET(HG_Mat,view_to_world);
};

