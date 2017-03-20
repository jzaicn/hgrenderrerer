#pragma once
#include "HG_BaseModel.h"
class HG_Camera
{
public:
	HG_Camera(void);
	~HG_Camera(void);

private:
	EH_Camera* create();
public:
	void saveTo(_Out_ EH_Camera& _camera);
	void loadFrom(const EH_Camera& _camera);

private:
	GETSET(EH_Camera*,camera);

	GETSET(float,fov);
	GETSET(float,near_clip);
	GETSET(float,far_clip);
	GETSET(uint_t,image_width);
	GETSET(uint_t,image_height);
	GETSET(bool,cubemap_render);

	GETSET_VECTYPE(EH_Mat,view_to_world);
};

