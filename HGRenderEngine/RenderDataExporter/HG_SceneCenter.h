#pragma once

#include <vector>
#include "HG_Camera.h"
#include "HG_Light.h"
#include "HG_Mesh.h"
#include "HG_Material.h"
#include "HG_MeshInstance.h"
#include "HG_BaseModel.h"

class HG_SceneCenter
{
public:
	HG_SceneCenter(void);
	~HG_SceneCenter(void);
public:
	std::string debug()
	{
		return "";
	}	
	
	static HG_SceneCenter m_inst;
	static HG_SceneCenter& inst()
	{
		return m_inst;
	}

	
// 	template <typename T> 
// 	void checkAndPushBack(std::vector<T>& vec,T& item)
// 	{
// 		for (int i = 0; i < vec.size() ; i++)
// 		{
// 			if (vec.at(i).getUniqueCode().compare(item.getUniqueCode()) == 0)
// 			{
// 				vec[i] = item;
// 				return;
// 			}
// 		}
// 		vec.push_back(item);
// 	}

	void addMesh(HG_Mesh mesh)
	{
		for (int i = 0; i < m_meshList.size() ; i++)
		{
			if (m_meshList.at(i).getUniqueCode().compare(mesh.getUniqueCode()) == 0)
			{
				m_meshList[i] = mesh;
				return;
			}
		}
		m_meshList.push_back(mesh);
	}

	void addMaterial(HG_Material material)
	{
		for (int i = 0; i < m_materialList.size() ; i++)
		{
			if (m_materialList.at(i).getUniqueCode().compare(material.getUniqueCode()) == 0)
			{
				m_materialList[i] = material;
				return;
			}
		}
		m_materialList.push_back(material);
	}

	void addMeshUseMaterial(HG_MeshInstance inst)
	{
		for (int i = 0; i < m_meshInstanceList.size() ; i++)
		{
			if (m_meshInstanceList.at(i).getUniqueCode().compare(inst.getUniqueCode()) == 0)
			{
				m_meshInstanceList[i] = inst;
				return;
			}
		}
		m_meshInstanceList.push_back(inst);
	}


private:
	//camera
	GETSET(std::vector<HG_Camera>,cameraList);

	//light
	GETSET(std::vector<HG_Light>,lightList);

	//mesh
	GETSET(std::vector<HG_Mesh>,meshList);

	//material
	GETSET(std::vector<HG_Material>,materialList);

	//mesh实例 多大，在哪，方向，和什么材质关联，用的是哪个实例
	GETSET(std::vector<HG_MeshInstance>,meshInstanceList);
	
};

