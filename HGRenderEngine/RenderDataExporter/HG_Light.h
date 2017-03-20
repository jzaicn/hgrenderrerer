#pragma once
#include "HG_BaseModel.h"
class HG_Light
{
public:
	HG_Light(void);
	~HG_Light(void);


private:
	EH_Light* create();

public:
	void loadFrom(const EH_Light& light);
	void saveTo(_Out_ EH_Light& light);

private:
	GETSET(EH_Light*,light);
	
	GETSET(EH_LightType,type);
	GETSET(CString,ies_filename);	
	GETSET(float,intensity);
	GETSET_VECTYPE(EH_Vec2,size);		
	GETSET_VECTYPE(EH_Mat,light_to_world);		


};

