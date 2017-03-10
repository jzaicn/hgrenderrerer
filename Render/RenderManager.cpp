#include "StdAfx.h"
#include "RenderManager.h"
#include "HgLog/HgLog.h"

RenderManager* RenderManager::render = NULL;

RenderManager::RenderManager(void)
{
}


RenderManager::~RenderManager(void)
{
}

RenderManager& RenderManager::RenderManager::getInstance()
{
	if (!render)
	{
		render = new RenderManager();
		if (!render)
		{
			throw std::runtime_error("创建管理器失败");
		}
	}
	return *render;
}

void RenderManager::saveImage(CString path)
{
	
}

void RenderManager::saveESS(CString path)
{
	EH_begin_export(m_core.RenderContext(),path.GetBuffer(),m_exportOptions.ExportOption());
}

void RenderManager::breakSaveESS()
{
	EH_end_export();
}

void RenderManager::initialRenderCore()
{
	
}

void RenderManager::initialRenderLog()
{
	EH_set_log_callback(m_core.RenderContext(),(RenderManager::loggingCallBack));
}

void RenderManager::initialRenderProc()
{
	EH_set_progress_callback(m_core.RenderContext(),(RenderManager::processingCallBack));
}

void RenderManager::startRenderCore()
{

}

void RenderManager::pauseRenderCore()
{

}

void RenderManager::stopRenderCore()
{

}

void RenderManager::setRenderOption()
{

}

void RenderManager::setCamera()
{

}

void RenderManager::setMesh()
{

}

void RenderManager::setMaterial()
{

}

void RenderManager::setMeshNodeRefToMesh()
{

}

void RenderManager::setLight()
{

}

void RenderManager::setSky()
{

}

void RenderManager::setSun()
{

}

void RenderManager::loggingCallBack(EH_Severity severity, const char *msg)
{

}

void RenderManager::processingCallBack(float progress)
{

}
