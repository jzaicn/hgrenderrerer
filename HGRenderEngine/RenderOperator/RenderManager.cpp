#include "StdAfx.h"
#include "RenderManager.h"



RenderManager::RenderManager(void)
{
}


RenderManager::~RenderManager(void)
{
}

RenderManager RenderManager::manager;

RenderManager& RenderManager::inst()
{
	return * this;
}
