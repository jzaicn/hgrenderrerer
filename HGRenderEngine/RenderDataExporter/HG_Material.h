#pragma once
#include "HG_BaseModel.h"

class HG_Material :public HG_BaseModel
{
public:
	HG_Material(void);
	~HG_Material(void);

	typedef enum{
		empty,
		image,
		color
	}MType;


	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

private:

	GETSET(MType,type);
	GETSET(std::string,image);
	GETSET(std::string,unique_code);
	GETSET(HG_Vec4,color);
};

