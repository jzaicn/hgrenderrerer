#include "StdAfx.h"
#include "HG_Light.h"
#include <stdexcept>

HG_Light::HG_Light(void)
{
	set_type(spot_light);
	set_ies_filename("");
	set_intensity(0);
	set_size(HG_Vec2(0,0));
	set_light_to_world(HG_Mat());
}


HG_Light::~HG_Light(void)
{
	
}

