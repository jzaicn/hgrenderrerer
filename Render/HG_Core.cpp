#include "StdAfx.h"
#include "HG_Core.h"


HG_Core::HG_Core(void)
{
	RenderContext(EH_create());
}


HG_Core::~HG_Core(void)
{	
	EH_delete(RenderContext());
}
