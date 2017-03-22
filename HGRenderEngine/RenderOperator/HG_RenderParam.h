#pragma once
#include "HG_BaseModel.h"

class HG_RenderParam :public HG_BaseModel
{
public:
	HG_RenderParam(void)
	{
		set_render_width(0);
		set_render_height(0);
		set_render_quality(0);
	}

	~HG_RenderParam(void)
	{

	}

	HG_RenderParam(const HG_RenderParam& other)	
	{
		set_render_width(other.get_render_width());
		set_render_height(other.get_render_height());
		set_render_quality(other.get_render_quality());
	}

	HG_RenderParam& operator=(const HG_RenderParam &other)	
	{
		set_render_width(other.get_render_width());
		set_render_height(other.get_render_height());
		set_render_quality(other.get_render_quality());
		return *this;
	}



	virtual std::string get_classname() override
	{
		return "HG_RenderParam";
	}

	virtual void save(Json::Value& out) override
	{
		out["render_width"] = get_render_width();
		out["render_height"] = get_render_height();
		out["render_quality"] = get_render_quality();
	}

	virtual void load(const Json::Value& in) override
	{
		set_render_width(in["render_width"].asUInt());
		set_render_height(in["render_height"].asUInt());
		set_render_quality(in["render_quality"].asUInt());
	}

private:
	GETSET(UINT,render_width);
	GETSET(UINT,render_height);
	GETSET(UINT,render_quality);

};

