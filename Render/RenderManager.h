#pragma once
#include "ElaraHomeAPI.h"
#include "HG_Core.h"
#include "HG_ExportOptions.h"
#include "HG_Camera.h"
#include "HG_Mesh.h"
#include "HG_Material.h"
#include "HG_MeshInstance.h"
#include "HG_Light.h"
#include "HG_Sky.h"
#include "HG_Sun.h"
#include <map>

class RenderManager
{
private:
	RenderManager(void);
	~RenderManager(void);

public:
	static RenderManager& getInstance();
	void saveImage(CString path);
	void saveESS(CString path);
	void breakSaveESS();

	void initialRenderCore();
	void initialRenderLog();
	void initialRenderProc();

public:
	void startRenderCore();
	void pauseRenderCore();
	void stopRenderCore();

private:
	void useRenderOption();
	void useCamera();
	void useMesh();
	void useMaterial();
	void useMeshInstance();
	void useLight();
	void useSky();
	void useSun();


public:
	static void loggingCallBack(EH_Severity severity, const char *msg);
	static bool processingCallBack(float progress);

private:
	GETSET(HG_Core,core);

	static RenderManager* render;

	HG_ExportOptions m_exportOptions;
	std::vector<HG_Camera> m_camera;
	std::map<CString,HG_Mesh> m_mesh;
	std::map<CString,HG_Material> m_material;
	std::map<CString,HG_MeshInstance> m_meshInstance;
	std::map<CString,HG_Light> m_light;
	
	std::vector<HG_Sky> m_sky;
	std::vector<HG_Sun> m_sun;
};

