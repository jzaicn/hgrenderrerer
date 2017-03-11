#include "StdAfx.h"
#include "HG_Sun.h"

#include <stdexcept>

HG_Sun::HG_Sun(void)
{
	m_enabled = true;
	m_intensity = 10.0;
	m_color = 0xFFFFFFFF;	//WHITE	
	m_soft_shadow = 1.0;
	m_angle = 0.0;
	m_height = 20.0;
	
	set_sun(create());
}


HG_Sun::~HG_Sun(void)
{
	if (get_sun())
	{
		free(get_sun());
		set_sun(NULL);
	}
}

EH_Sun* HG_Sun::create()
{
	EH_Sun* val = (EH_Sun*)(malloc(sizeof(EH_Sun)));
	if (!val)
	{
		throw std::runtime_error("EH_Sun ´´½¨Ê§°Ü");
	}
	saveTo(*val);
	return val;
}

void HG_Sun::saveTo(_Out_ EH_Sun& sun)
{
	sun.enabled = get_enabled();
	sun.intensity = get_intensity();
	sun.soft_shadow = get_soft_shadow();
	sun.dir[0] = get_angle();
	sun.dir[1] = get_height();
	
	sun.color[0] = GetRValue(m_color);	//R
	sun.color[1] = GetGValue(m_color);	//G
	sun.color[2] = GetBValue(m_color);	//B
}

void HG_Sun::loadFrom(const EH_Sun& sun)
{
	set_enabled(sun.enabled);
	set_intensity(sun.intensity);
	set_soft_shadow(sun.soft_shadow);

	m_color = RGB( sun.color[0], sun.color[1], sun.color[2] );

	set_angle(sun.dir[0]);
	set_height(sun.dir[1]);
}
