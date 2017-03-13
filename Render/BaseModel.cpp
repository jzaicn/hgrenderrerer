#include "StdAfx.h"
#include "BaseModel.h"
#include <stdexcept>

BaseModel::BaseModel(void)
{
}


BaseModel::~BaseModel(void)
{
}

HG_Vec3::HG_Vec3(void)
{
	set_x(0);
	set_y(0);
	set_z(0);
}

HG_Vec3::~HG_Vec3(void)
{

}

EH_Vec* HG_Vec3::create()
{
	EH_Vec* val = (EH_Vec*)(malloc(sizeof(EH_Vec)));
	if (!val)
	{
		throw std::runtime_error("EH_Vec 创建失败");
	}
	saveTo(*val);
	return val;
}

void HG_Vec3::saveTo(_Out_ EH_Vec& vec)
{
	vec[0] = m_x;
	vec[1] = m_y;
	vec[2] = m_z;
}

void HG_Vec3::loadFrom(const EH_Vec& vec)
{
	m_x = vec[0];
	m_y = vec[1];
	m_z = vec[2];
}

HG_Vec2::HG_Vec2(void)
{
	set_x(0);
	set_y(0);
}

HG_Vec2::~HG_Vec2(void)
{

}

EH_Vec2* HG_Vec2::create()
{
	EH_Vec2* val = (EH_Vec2*)(malloc(sizeof(EH_Vec2)));
	if (!val)
	{
		throw std::runtime_error("EH_Vec 创建失败");
	}
	saveTo(*val);
	return val;
}

void HG_Vec2::saveTo(_Out_ EH_Vec2& vec)
{
	vec[0] = m_x;
	vec[1] = m_y;
}

void HG_Vec2::loadFrom(const EH_Vec2& vec)
{
	m_x = vec[0];
	m_y = vec[1];
}