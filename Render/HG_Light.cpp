#include "StdAfx.h"
#include "HG_Light.h"
#include <stdexcept>

HG_Light::HG_Light(void)
{
	set_light(create());
}


HG_Light::~HG_Light(void)
{
	if (get_light())
	{
		free(get_light());
		set_light(NULL);
	}
}

EH_Light* HG_Light::create()
{
	EH_Light* light = (EH_Light*)(malloc(sizeof(EH_Light)));
	if (!light)
	{
		throw std::runtime_error("HG_Light ´´½¨Ê§°Ü");
	}
	saveTo(*light);
	return light;
}

void HG_Light::loadFrom(const EH_Light& light)
{
	set_type(light.type);
	set_ies_filename(light.ies_filename);
	set_intensity(light.intensity);
	set_size(&light.size);
	set_light_to_world(&light.light_to_world);
}

void HG_Light::saveTo(_Out_ EH_Light& light)
{
	light.type = get_type();
	light.ies_filename = get_ies_filename().GetBuffer();
	light.intensity = get_intensity();
	get_size(&light.size);
	get_light_to_world(&light.light_to_world);
}
