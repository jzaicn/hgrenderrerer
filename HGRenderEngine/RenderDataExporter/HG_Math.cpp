
#include "StdAfx.h"
#include "HG_Math.h"
#include <limits>

HG_Math::HG_Math(void)
{
}

HG_Math::~HG_Math(void)
{
}

//compare float
bool HG_Math::compareF(float a, float b)
{
	if(fabs(a - b) < std::numeric_limits<float>::epsilon())
		return true;
	return false;
}
