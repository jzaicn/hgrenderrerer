#include "StdAfx.h"
#include "HG_Core.h"


HG_Core::HG_Core(void)
{
	set_renderContext(NULL);
	set_renderContext(create());
}


HG_Core::~HG_Core(void)
{	
	if (get_renderContext())
	{
		EH_delete(get_renderContext());
		set_renderContext(NULL);
	}
}

EH_Context* HG_Core::create()
{
	return EH_create();
}

