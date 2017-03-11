#include "StdAfx.h"
#include "HG_Camera.h"
#include <stdexcept>

HG_Camera::HG_Camera(void)
{
	m_near_clip = 0.0;
	m_far_clip = 0.0;
	m_image_width = 0;
	m_image_height = 0;
	m_cubemap_render = false;
	clear_view_to_world();

	set_camera(create());
}


HG_Camera::~HG_Camera(void)
{
	if (get_camera())
	{
		free(get_camera());
		set_camera(NULL);
	}
}

EH_Camera* HG_Camera::create()
{
	EH_Camera* camera = (EH_Camera*)(malloc(sizeof(EH_Camera)));
	if (!camera)
	{
		throw std::runtime_error("EH_Camera ´´½¨Ê§°Ü");
	}
	saveTo(*m_camera);
	return camera;
	
}

void HG_Camera::saveTo(_Out_ EH_Camera& _camera)
{
	_camera.fov = m_fov;
	_camera.near_clip = m_near_clip;
	_camera.far_clip = m_far_clip;
	_camera.image_width = m_image_width;
	_camera.image_height = m_image_height;
	_camera.cubemap_render = m_cubemap_render;
	get_view_to_world(&_camera.view_to_world);
}


void HG_Camera::loadFrom(const EH_Camera& _camera)
{
	m_near_clip = _camera.near_clip;
	m_far_clip = _camera.far_clip;
	m_image_width = _camera.image_width;
	m_image_height = _camera.image_height;
	m_cubemap_render = _camera.cubemap_render;
	set_view_to_world(&(_camera.view_to_world));
}
