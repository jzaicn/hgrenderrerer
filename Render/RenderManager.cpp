#include "StdAfx.h"
#include "RenderManager.h"
#include "HgLog/HgLog.h"
#include <ei.h>

#pragma comment(lib,"liber.lib")
#pragma comment(lib,"oslcomp.lib")
#pragma comment(lib,"oslexec.lib")
#pragma comment(lib,"oslquery.lib")

RenderManager* RenderManager::render = NULL;

RenderManager::RenderManager(void)
{
}


RenderManager::~RenderManager(void)
{
}

RenderManager& RenderManager::getInstance()
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

//////////////////////////////////////////////////////////////////////////
// 导出ess文件

void RenderManager::saveESS(CString path)
{
	EH_begin_export(m_core.get_renderContext(),path.GetBuffer(),m_exportOptions.get_exportOption());
}

void RenderManager::breakSaveESS()
{
	EH_end_export();
}


void RenderManager::initialRenderCore()
{
	
}



//////////////////////////////////////////////////////////////////////////
// 操作控制

void RenderManager::startRenderCore()
{
	bool ignore_render = true;
	bool display = true;
	bool interactive = true;
	bool force_render = true;

	CString filename = "E:\\HGRENDER\\Elara_SDK_1_0_76\\bin\\default.ess";

	//if (!ei_parse2(filename, ignore_render || display || interactive || force_render))
	{
		//ei_error("Failed to parse file: %s\n", filename);
		throw std::runtime_error("Failed to parse file");
	}
}

void RenderManager::pauseRenderCore()
{

}

void RenderManager::stopRenderCore()
{

}

void RenderManager::useRenderOption()
{

}

//////////////////////////////////////////////////////////////////////////
// 设置资源
#if 1
// 添加摄像机到场景中
void RenderManager::useCamera()
{
	for (UINT i = (UINT)m_camera.size() - 1; i >= 0 ; i--)
	{
		HG_Camera camera = m_camera.at(i);
		EH_set_camera(m_core.get_renderContext(),camera.get_camera());
	}
}

// 添加场景中所有mesh实例
void RenderManager::useMesh()
{
	for (auto it = m_mesh.begin() ; it!= m_mesh.end() ; ++it)
	{
		CString name = it->first;
		HG_Mesh mesh = it->second;
		EH_add_mesh(m_core.get_renderContext(),name.GetBuffer(),mesh.get_mesh());
	}
}
// 添加场景中所有材质实例
void RenderManager::useMaterial()
{
	for (auto it = m_material.begin() ; it!= m_material.end() ; ++it)
	{
		CString name = it->first;
		HG_Material material = it->second;
		EH_add_material(m_core.get_renderContext(),name.GetBuffer(),material.get_material());
	}
	
}
// 添加场景中所有mesh所在位置
void RenderManager::useMeshInstance()
{
	for (auto it = m_meshInstance.begin() ; it!= m_meshInstance.end() ; ++it)
	{
		CString name = it->first;
		HG_MeshInstance inst = it->second;
		EH_add_mesh_instance(m_core.get_renderContext(),name.GetBuffer(),inst.get_meshInstance());
	}
}

void RenderManager::useLight()
{
	for (auto it = m_light.begin() ; it!= m_light.end() ; ++it)
	{
		CString name = it->first;
		HG_Light light = it->second;
		EH_add_light(m_core.get_renderContext(),name.GetBuffer(),light.get_light());
	}
}

//设置天空
void RenderManager::useSky()
{
	for (UINT i = 0; i < m_sky.size() ; i++)
	{
		HG_Sky sky = m_sky.at(i);
		EH_set_sky(m_core.get_renderContext(),sky.get_sky());
	}
}

//设置天空
void RenderManager::useSun()
{
	for (UINT i = 0; i < m_sun.size() ; i++)
	{
		HG_Sun sun = m_sun.at(i);	
		EH_set_sun(m_core.get_renderContext(),sun.get_sun());
	}
}

#endif
//////////////////////////////////////////////////////////////////////////
// 设置关联句柄

#if 1
void RenderManager::initialRenderLog()
{
	EH_set_log_callback(m_core.get_renderContext(),(RenderManager::loggingCallBack));
}

void RenderManager::initialRenderProc()
{
	EH_set_progress_callback(m_core.get_renderContext(),(RenderManager::processingCallBack));
}

//////////////////////////////////////////////////////////////////////////
// 响应句柄

void RenderManager::loggingCallBack(EH_Severity severity, const char *msg)
{
	HGLOG_DEBUG("level %d : %s",severity,msg);
	return;
}

bool RenderManager::processingCallBack(float progress)
{
	HGLOG_DEBUG("processingCallBack %f",progress);
	return true;
}

#endif