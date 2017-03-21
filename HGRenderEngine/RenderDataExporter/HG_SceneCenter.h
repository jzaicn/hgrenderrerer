#pragma once

#include <vector>
#include "HG_Camera.h"
#include "HG_Light.h"
#include "HG_Mesh.h"
#include "HG_Material.h"
#include "HG_MeshInstance.h"
#include "HG_BaseModel.h"
#include "HG_ModelInstance.h"

class HG_SceneCenter : HG_BaseModel
{
public:
	HG_SceneCenter(void);
	~HG_SceneCenter(void);
	HG_SceneCenter(const HG_SceneCenter& other)	
	{
		set_cameraList(other.get_cameraList());
		set_lightList(other.get_lightList());
		set_meshList(other.get_meshList());
		set_modelList(other.get_modelList());
		set_materialList(other.get_materialList());
		set_meshInstanceList(other.get_meshInstanceList());
	}

	HG_SceneCenter& operator=(const HG_SceneCenter &other)	
	{
		set_cameraList(other.get_cameraList());
		set_lightList(other.get_lightList());
		set_meshList(other.get_meshList());
		set_modelList(other.get_modelList());
		set_materialList(other.get_materialList());
		set_meshInstanceList(other.get_meshInstanceList());
	}

	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

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

	
	template <typename T> 
	void checkAndPushBack(std::vector<T>& vec,T& item)
	{
		for (UINT i = 0; i < vec.size() ; i++)
		{
			if (vec.at(i).get_unique_code().compare(item.get_unique_code()) == 0)
			{
				vec[i] = item;
				return;
			}
		}
		vec.push_back(item);
	}

	void addModelInstance(HG_ModelInstance model)
	{
		checkAndPushBack(m_modelList,model);
	}

	void addMesh(HG_Mesh mesh)
	{
		checkAndPushBack(m_meshList,mesh);
	}

	void addMaterial(HG_Material material)
	{
		checkAndPushBack(m_materialList,material);
	}

	void addMeshUseMaterial(HG_MeshInstance instance)
	{
		checkAndPushBack(m_meshInstanceList,instance);
	}


private:
	//camera
	GETSET(std::vector<HG_Camera>,cameraList);

	//light
	GETSET(std::vector<HG_Light>,lightList);

	//mesh
	GETSET(std::vector<HG_Mesh>,meshList);

	//model
	GETSET(std::vector<HG_ModelInstance>,modelList);

	//material
	GETSET(std::vector<HG_Material>,materialList);

	//mesh实例 多大，在哪，方向，和什么材质关联，用的是哪个实例
	GETSET(std::vector<HG_MeshInstance>,meshInstanceList);
	
};

