#pragma once

#include "BaseModel.h"
class HG_Sun
{
public:
	HG_Sun(void);
	~HG_Sun(void);

private:
	EH_Sun* create() ;
public:
	void saveTo(_Out_ EH_Sun& sky) ;


	void loadFrom(const EH_Sun& sky) ;


private:
	GETSET(EH_Sun*,sun);

	GETSET(bool,enabled);
	GETSET(float,intensity);
	GETSET(COLORREF,color);
	GETSET(float,soft_shadow);
	GETSET(float,angle);
	GETSET(float,height);


};

