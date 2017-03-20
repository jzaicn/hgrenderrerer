#pragma once
#include "HG_BaseModel.h"

class HG_Light :public HG_BaseModel
{
public:
	HG_Light(void);
	~HG_Light(void);

	typedef enum {
		spot_light,
		point_light,
		flat_light,
	}LightType;

private:
	
	GETSET(LightType,type);
	GETSET(std::string,ies_filename);	
	GETSET(float,intensity);
	GETSET(HG_Vec2,size);		
	GETSET(HG_Mat,light_to_world);		


};

