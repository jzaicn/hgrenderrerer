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

private:

	GETSET(MType,type);
	GETSET(std::string,image);
	GETSET(HG_Vec4,color);
	GETSET(std::string,unique_code);
};

