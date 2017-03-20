#pragma once

#include <vector>
#include "HG_Camera.h"
#include "HG_Light.h"
#include "HG_Mesh.h"
#include "HG_Material.h"
#include "HG_MeshInstance.h"

#include "BaseModel.h"

class HGSceneCenter
{
public:
	HGSceneCenter(void);
	~HGSceneCenter(void);
public:
	void debug();
	
	HGSceneCenter& inst();
	
	void addMesh(HG_Mesh mesh);

	void addMaterial(HG_Material material);

	void addMeshUseMaterial();

private:
	//camera
	GETSET(std::vector<HG_Camera>,m_cameraList);

	//light
	GETSET(std::vector<HG_Light>,m_lightList);

	//mesh
	GETSET(std::vector<HG_Mesh>,m_meshList);

	//material
	GETSET(std::vector<HG_Material>,m_materialList);

	//mesh实例 多大，在哪，方向，和什么材质关联，用的是哪个实例
	GETSET(std::vector<HG_MeshInstance>,m_meshInstanceList);
	
};

