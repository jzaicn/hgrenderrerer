#pragma once

#include "BaseModel.h"
class HG_Sky
{
public:
	HG_Sky(void);
	~HG_Sky(void);

private:
	EH_Sky* create() ;
public:
	 void saveTo(_Out_ EH_Sky& sky) ;


	 void loadFrom(const EH_Sky& sky) ;

private:
	GETSET(EH_Sky*,sky);


	GETSET(bool ,enabled);
	GETSET(float ,intensity);
	GETSET(CString, hdri_name);
	GETSET(float ,hdri_rotation);


};

