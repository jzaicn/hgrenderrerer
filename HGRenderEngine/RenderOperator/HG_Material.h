#pragma once
#include "HG_BaseModel.h"

class HG_Material :public HG_BaseModel
{
public:
	//类型分类
	typedef enum{
		color,
		image,
	}MType;
	
	//白色默认
	static HG_Material Material_ColorWhite;

	HG_Material(void)
	{
		set_type(color);
		set_image("");
		set_color(HG_Vec4(1.0,1.0,1.0,1.0));
		set_cull_back(true);
	};
	~HG_Material(void);

	HG_Material(UINT material_color,bool cull = true)
	{
		set_color(HG_Vec4(material_color));
		set_type(color);
		set_image("");
		set_cull_back(cull);
	};
	HG_Material(HG_Vec4 material_color,bool cull = true)
	{
		set_type(color);
		set_image("");
		set_color(material_color);
		set_cull_back(cull);
	};
	HG_Material(std::string image_path,bool cull = true)
	{
		set_type(image);
		set_image(image_path);
		set_color(HG_Vec4());
		set_cull_back(cull);
	};

	HG_Material(const HG_Material& other)	
	{
		set_type(other.get_type());
		set_image(other.get_image());
		set_unique_code(other.get_unique_code());
		set_color(other.get_color());
		set_cull_back(other.get_cull_back());
	}

	HG_Material& operator=(const HG_Material &other)	
	{
		set_type(other.get_type());
		set_image(other.get_image());
		set_unique_code(other.get_unique_code());
		set_color(other.get_color());
		set_cull_back(other.get_cull_back());
		return *this;
	}

	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

private:

	GETSET(MType,type);
	GETSET(std::string,image);
	GETSET(std::string,unique_code);
	GETSET(HG_Vec4,color);
	GETSET(bool,cull_back);
};

