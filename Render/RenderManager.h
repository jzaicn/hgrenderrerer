#pragma once
#include "ElaraHomeAPI.h"
#include "HG_Core.h"
#include "HG_ExportOptions.h"

class RenderManager
{
private:
	RenderManager(void);
	~RenderManager(void);

	static RenderManager* render;

public:
	static RenderManager& getInstance();
	void saveImage(CString path);
	void saveESS(CString path);
	void breakSaveESS();

	void initialRenderCore();
	void initialRenderLog();
	void initialRenderProc();


	void startRenderCore();
	void pauseRenderCore();
	void stopRenderCore();

	void setRenderOption();
	void setCamera();
	void setMesh();
	void setMaterial();
	void setMeshNodeRefToMesh();
	void setLight();
	void setSky();
	void setSun();
	

public:
	static void loggingCallBack(EH_Severity severity, const char *msg);
	static bool processingCallBack(float progress);

private:
	HG_Core m_core;
	HG_ExportOptions m_exportOptions;
};

