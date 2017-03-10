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
	
	m_sun = create();
}


HG_Sun::~HG_Sun(void)
{
	if (m_sun)
	{
		free(m_sun);
	}
}

EH_Sun* HG_Sun::create()
{
	EH_Sun* sun = (EH_Sun*)(malloc(sizeof(EH_Sun)));
	if (!m_sun)
	{
		throw std::runtime_error("EH_Sun´´½¨Ê§°Ü");
	}
	memset(sun,0,sizeof(EH_Sun));
	saveToSun(*sun);
	return sun;
}

void HG_Sun::saveToSun(_Out_ EH_Sun& sun)
{
	sun.enabled = m_enabled;
	sun.intensity = m_intensity;
	sun.color[0] = GetRValue(m_color);	//R
	sun.color[1] = GetGValue(m_color);	//G
	sun.color[2] = GetBValue(m_color);	//B
	sun.soft_shadow = m_soft_shadow;
	sun.dir[0] = m_angle;
	sun.dir[1] = m_height;
}

void HG_Sun::loadFromSun(const EH_Sun& sun)
{
	m_enabled = sun.enabled;
	m_intensity = sun.intensity;
	m_color = RGB( sun.color[0], sun.color[1], sun.color[2] );
	m_soft_shadow = sun.soft_shadow;
	m_angle = sun.dir[0];
	m_height = sun.dir[1];
}
