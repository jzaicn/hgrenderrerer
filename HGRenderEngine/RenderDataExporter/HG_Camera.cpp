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
}


HG_Camera::~HG_Camera(void)
{
}

