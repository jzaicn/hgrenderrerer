#pragma once
#include "HG_BaseModel.h"

class HG_Config
{
private:
	HG_Config(void)
	{
		//需要设置到\\结束 ex: "D:\\***\\"
		m_export_path = ("D:\\export\\");
		m_texture_relative_path = ("textures\\");
	}

	~HG_Config(void)
	{

	}
public:

	static HG_Config& inst()
	{
		return m_config;
	}
	
	std::string get_texture_export_path(std::string texture_name)
	{
		return m_export_path + m_texture_relative_path + texture_name;
	}

private:
	static HG_Config m_config;
	std::string m_export_path;
	std::string m_texture_relative_path;
};

