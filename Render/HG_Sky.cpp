#include "StdAfx.h"
#include "HG_Sky.h"
#include <stdexcept>

HG_Sky::HG_Sky(void)
{
	set_enabled(true);
	set_intensity(0);
	set_hdri_name("");
	set_hdri_rotation(0);

	set_sky(create());
}


HG_Sky::~HG_Sky(void)
{
	if (get_sky())
	{
		free(get_sky());
		set_sky(NULL);
	}
}


EH_Sky* HG_Sky::create()
{
	HG_Sky* val = (HG_Sky*)(malloc(sizeof(HG_Sky)));
	if (!val)
	{
		throw std::runtime_error("HG_Sky ´´½¨Ê§°Ü");
	}
	saveTo(*val);
	return val;
}

void HG_Sky::saveTo(_Out_ EH_Sky& sky)
{
	sky.enabled = get_enabled();
	sky.hdri_name = get_hdri_name();
	sky.intensity = get_intensity();
	sky.hdri_rotation = get_hdri_rotation();
}

void HG_Sky::loadFrom(const EH_Sky& sky)
{
	set_enabled(sky.enabled);
	set_hdri_name(sky.hdri_name);
	set_intensity(sky.intensity);
	set_hdri_rotation(sky.hdri_rotation);
}
