#include "StdAfx.h"
#include "RenderManager.h"


RenderManager RenderManager::manager;

RenderManager::RenderManager(void)
{
	set_render_exe_path("E:\\HGRENDER\\Elara_SDK_1_0_76\\bin\\er.exe");
	set_scene_path("D:\\scene.ess");
}


RenderManager::~RenderManager(void)
{
}


RenderManager& RenderManager::inst()
{
	return manager;
}

void RenderManager::SaveESS(std::string path)
{
	set_scene_path(path);

	
}

void RenderManager::Begin()
{
	CString cmdRunRender;
	cmdRunRender.Format("%s -display %s",get_render_exe_path().c_str(),get_scene_path().c_str());
	system(cmdRunRender.GetBuffer());
}
