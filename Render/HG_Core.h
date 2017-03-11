#pragma once

#include "BaseModel.h"

class HG_Core
{
public:
	HG_Core(void);
	~HG_Core(void);


	EH_Context* create();


private:
	GETSET(EH_Context*,renderContext)
};

