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
		m_model_relative_path = ("models\\");
		m_model_ignore_path = ("Ironware\\连接类\\");
		m_execute_path = ("E:\\HGRENDER\\trunk\\HGRenderEngine\\x64\\Release\\");
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

	std::string get_model_export_path(std::string model_name)
	{
		return m_export_path + m_model_relative_path + model_name;
	}

	std::string get_model_ignore_path()
	{
		return m_model_ignore_path;
	}
	
	std::string get_file_path(std::string relative_file_path)
	{
		return m_execute_path + relative_file_path;
	}

	std::string get_file_export_path()
	{
		return m_model_ignore_path;
	}

private:
	static HG_Config m_config;
	std::string m_export_path;
	std::string m_texture_relative_path;
	std::string m_model_relative_path;
	std::string m_model_ignore_path;
	std::string m_execute_path;
};

