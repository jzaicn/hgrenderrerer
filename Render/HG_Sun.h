#pragma once

#include "ElaraHomeAPI.h"

class HG_Sun
{
public:
	HG_Sun(void);
	~HG_Sun(void);

	bool Enabled() const { return m_enabled; }
	void Enabled(bool val) { m_enabled = val; }

	float Intensity() const { return m_intensity; }
	void Intensity(float val) { m_intensity = val; }

	COLORREF Color() const { return m_color; }
	void Color(COLORREF val) { m_color = val; }

	float Soft_shadow() const { return m_soft_shadow; }
	void Soft_shadow(float val) { m_soft_shadow = val; }

	float Angle() const { return m_angle; }
	void Angle(float val) { m_angle = val; }

	float Height() const { return m_height; }
	void Height(float val) { m_height = val; }

private:
	bool m_enabled;
	float m_intensity;
	COLORREF m_color;
	float m_soft_shadow;
	float m_angle;
	float m_height;

public:
	EH_Sun* create();	
	
	EH_Sun Sun() 
	{
		saveToSun(m_sun);
		return m_sun; 
	}
	void Sun(EH_Sun val) 
	{
		loadFromSun(val);
	}

	void saveToSun(_Out_ EH_Sun& sun);

	void loadFromSun(const EH_Sun& sun);

private:
	EH_Sun m_sun;
};

