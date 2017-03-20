#pragma once
#include "HG_BaseModel.h"
class HG_Camera :public HG_BaseModel
{
public:
	HG_Camera(void);
	~HG_Camera(void);


	virtual std::string get_classname() { return "HG_Camera"; };
	virtual void save(Json::Value& out) override;
	virtual void load(const Json::Value& in) override;

private:

	GETSET(float,fov);
	GETSET(float,near_clip);
	GETSET(float,far_clip);
	GETSET(UINT,image_width);
	GETSET(UINT,image_height);
	GETSET(bool,cubemap_render);

	GETSET(HG_Mat,view_to_world);
};

