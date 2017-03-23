#pragma once

#include <vector>
#include "HG_Camera.h"
#include "HG_Light.h"
#include "HG_Mesh.h"
#include "HG_Material.h"
#include "HG_MeshInstance.h"
#include "HG_BaseModel.h"
#include "HG_ModelInstance.h"
#include "HG_Expouse.h"
#include "HG_SunLight.h"
#include "HG_SkyLight.h"
#include "HG_RenderParam.h"

class HG_SceneCenter : HG_BaseModel
{
private:
	HG_SceneCenter(void);
	~HG_SceneCenter(void);
public:
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


	static HG_SceneCenter m_inst;
	static HG_SceneCenter& inst()
	{
		return m_inst;
	}


	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

public:
	std::string debug()
	{
		return "";
	}	
	
	void clear()
	{
		ref_cameraList().clear();
		ref_lightList().clear();
		ref_meshList().clear();
		ref_modelList().clear();
		ref_materialList().clear();
		ref_meshInstanceList().clear();
		set_expouse(HG_Expouse());
		set_sky(HG_SkyLight());
		set_sun(HG_SunLight());
		set_param(HG_RenderParam());
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
	
	//曝光参数
	GETSET(HG_Expouse,expouse);

	//天空参数
	GETSET(HG_SkyLight,sky);

	//太阳参数
	GETSET(HG_SunLight,sun);

	//图片参数
	GETSET(HG_RenderParam,param);
};

