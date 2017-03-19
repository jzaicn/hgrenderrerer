#pragma once

#include <vector>
#include "HG_Camera.h"
#include "HG_Light.h"
#include "HG_Mesh.h"
#include "HG_Material.h"
#include "HG_MeshInstance.h"

class HGSceneCenter
{
public:
	HGSceneCenter(void);
	~HGSceneCenter(void);

	void debug();

private:
	//camera
	std::vector<HG_Camera> m_cameraList;

	//light
	std::vector<HG_Light> m_lightList;

	//mesh
	std::vector<HG_Mesh> m_meshList;

	//material
	std::vector<HG_Material> m_materialList;

	//meshʵ�� ������ģ����򣬺�ʲô���ʹ������õ����ĸ�ʵ��
	std::vector<HG_MeshInstance> m_meshInstanceList;
	
};

