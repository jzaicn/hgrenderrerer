#include "StdAfx.h"
#include "RenderManager.h"
#include "HG_SceneCenter.h"
#include "Elara/ElaraHomeAPI.h"
#include "HgLog/HgLog.h"


class RenderManager::DataStorageCore
{
//////////////////////////////////////////////////////////////////////////
// 易渲数据存储核心
public:
	DataStorageCore(){set_context(NULL);}
	~DataStorageCore(){	clear();}
	void clear(){if (get_context())	{EH_delete(get_context());set_context(NULL);}}
	void init(){clear();initWhenNot();}
	void initWhenNot(){if (!get_context()){set_context(EH_create());}}

private:
	GETSET(EH_Context*,context);

//////////////////////////////////////////////////////////////////////////
// 字符管理工具
public:
	const char* createConstChar(const std::string& val)
	{
		const char* temptext = val.c_str();
		char* new_char = (char*)malloc( sizeof(char) * (val.length() + 1) );
		strcpy_s(new_char,(val.length() + 1),temptext);
		m_charManager.push_back(new_char);
		return new_char;
	}
	void clearCharBuffer()
	{
		for (int i = 0; i < m_charManager.size() ; i++)
		{
			free(m_charManager.at(i));
			m_charManager[i] = NULL;
		}
		m_charManager.clear();
	}
private:
	std::vector<char*> m_charManager;

//////////////////////////////////////////////////////////////////////////
// 填充器
public:
	void fill(uint_t& outval,UINT inval)
	{
		outval = inval;
	}
	void fill(EH_RGB& outval,HG_Vec4 inval)
	{
		outval[0] = inval.get_x();
		outval[1] = inval.get_y();
		outval[2] = inval.get_z();
	}
	void fill(EH_RGBA& outval,HG_Vec4 inval)
	{
		outval[0] = inval.get_x();
		outval[1] = inval.get_y();
		outval[2] = inval.get_z();
		outval[3] = inval.get_w();
	}
	void fill(EH_RGB& outval,UINT inval)
	{
		outval[0] = GetRValue(inval) / 255.0;
		outval[1] = GetGValue(inval) / 255.0;
		outval[2] = GetBValue(inval) / 255.0;
	}
	void fill(EH_RGBA& outval,UINT inval)
	{
		outval[0] = GetRValue(inval) / 255.0;
		outval[1] = GetGValue(inval) / 255.0;
		outval[2] = GetBValue(inval) / 255.0;
	}
	void fill(EH_Vec& outval,HG_Vec3 inval)
	{
		outval[0] = inval.get_x();
		outval[1] = inval.get_y();
		outval[2] = inval.get_z();
	}
	void fill(EH_Vec2& outval,HG_Vec2 inval)
	{
		outval[0] = inval.get_x();
		outval[1] = inval.get_y();
	}
	void fill(EH_Mat& outval,HG_Mat inval)
	{
		outval[ 0] = inval.get_mat()[0].get_x();
		outval[ 1] = inval.get_mat()[0].get_y();
		outval[ 2] = inval.get_mat()[0].get_z();
		outval[ 3] = inval.get_mat()[0].get_w();
		outval[ 4] = inval.get_mat()[1].get_x();
		outval[ 5] = inval.get_mat()[1].get_y();
		outval[ 6] = inval.get_mat()[1].get_z();
		outval[ 7] = inval.get_mat()[1].get_w();
		outval[ 8] = inval.get_mat()[2].get_x();
		outval[ 9] = inval.get_mat()[2].get_y();
		outval[10] = inval.get_mat()[2].get_z();
		outval[11] = inval.get_mat()[2].get_w();
		outval[12] = inval.get_mat()[3].get_x();
		outval[13] = inval.get_mat()[3].get_y();
		outval[14] = inval.get_mat()[3].get_z();
		outval[15] = inval.get_mat()[3].get_w();
	}
	void fill(EH_Sun& outval,HG_SunLight inval)
	{
		outval.enabled = inval.get_sun_enable();
		outval.intensity = inval.get_sun_light_intensity();
		fill(outval.color,inval.get_sun_color());
		outval.soft_shadow = inval.get_soft_shadow();
		outval.dir[0] = inval.get_sun_angle();
		outval.dir[1] = inval.get_sun_height();
	}
	void fill(EH_Sky& outval,HG_SkyLight inval)
	{
		outval.enabled = inval.get_sky_light_enable();
		outval.intensity = inval.get_sky_light_intensity();
		outval.hdri_name = createConstChar(inval.get_hdr());
		outval.hdri_rotation = inval.get_hdr_rotate();
	}
	void fill(EH_Camera& outval,HG_Camera inval)
	{
		outval.fov = inval.get_fov();
		outval.near_clip = inval.get_near_clip();
		outval.far_clip = inval.get_far_clip();
		outval.image_width = inval.get_image_width();
		outval.image_height = inval.get_image_height();
		fill(outval.view_to_world,inval.get_view_to_world());
		outval.cubemap_render = inval.get_cubemap_render();
	}
	void fill(EH_Texture& outval,std::string inval)
	{
		outval.filename = createConstChar(inval);
		outval.repeat = 1;
	}
	void fill(EH_AssemblyInstance& outval,HG_ModelInstance inval)
	{
		outval.filename = createConstChar(inval.get_model_file());
		fill(outval.mesh_to_world,inval.get_mesh_to_world());
	}
	void fill(EH_MeshInstance& outval,HG_MeshInstance inval)
	{
		outval.mesh_name = createConstChar(inval.get_material_code());
		fill(outval.mesh_to_world,inval.get_mesh_to_world());
		outval.mtl_name = createConstChar(inval.get_material_code());
	}
	void fill(EH_Mesh& outval,HG_Mesh inval)
	{
		outval.num_verts = inval.get_verts().size();
		outval.num_faces = inval.get_faces().size();

		for (int i = 0; i < inval.get_verts().size() ; i++)
		{
			fill((EH_Vec)(outval.verts[i]),inval.get_verts().at(i));
			fill((EH_Vec)(outval.normals[i]),inval.get_normals().at(i));
			fill((EH_Vec2)(outval.uvs[i]),inval.get_uvs().at(i));
		}
		
		
		for (int i = 0; i < inval.get_faces().size() ; i++)
		{
			fill((uint_t)(outval.face_indices[i+0]),inval.get_faces().at(i).get_t1());
			fill((uint_t)(outval.face_indices[i+1]),inval.get_faces().at(i).get_t2());
			fill((uint_t)(outval.face_indices[i+2]),inval.get_faces().at(i).get_t3());
		}
	}

	void fill(EH_Material& outval,HG_Material inval)
	{
		outval.backface_cull = inval.get_cull_back();
		

		fill(outval.diffuse_color,HG_Vec4());
		outval.diffuse_tex.filename = NULL;
		outval.diffuse_tex.repeat = 1.0;
// 		if (inval.get_type() == HG_Material::color)
// 		{
// 			fill((EH_RGB)outval.diffuse_color,inval.get_color());
// 		}
// 		if (inval.get_type() == HG_Material::image)
// 		{
// 			fill(outval.diffuse_tex,inval.get_image());
// 		}
		
		outval.diffuse_weight = 1.0;
		outval.roughness = 1.0;
		outval.backlight = 1.0;

		outval.specular_weight = 1.0;
		fill(outval.specular_color,HG_Vec4());
		outval.specular_tex.filename = NULL;
		outval.specular_tex.repeat = 1.0;
		outval.glossiness = 1.0;
		outval.specular_fresnel = 1.0;
		outval.anisotropy = 1.0;
		outval.rotation = 1.0;

		outval.transp_weight = 1.0;
		outval.transp_invert_weight = 1.0;
		outval.transp_tex.filename = NULL;
		outval.transp_tex.repeat = 1.0;

		outval.bump_weight = 1.0;
		outval.bump_tex.filename = NULL;
		outval.bump_tex.repeat = 1.0;
		outval.normal_bump = 1.0;

		outval.mirror_weight = 1.0;
		fill(outval.mirror_color,HG_Vec4());
		outval.mirror_fresnel = 1.0;

		outval.refract_weight = 1.0;
		outval.refract_invert_weight = 1.0;
		fill(outval.refract_color,HG_Vec4());
		outval.ior = 1.0;
		outval.refract_glossiness = 1.0;
	}


};




RenderManager RenderManager::manager;
RenderManager::DataStorageCore RenderManager::storage;


RenderManager::RenderManager(void)
{
	set_render_exe_path("E:\\HGRENDER\\Elara_SDK_1_0_76\\bin\\er.exe");
	set_scene_path("D:\\my_scene.ess");
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
	
	storage.initWhenNot();

	EH_ExportOptions opt;
	opt.base85_encoding = true;
	opt.left_handed = false;

	EH_begin_export(storage.get_context(),get_scene_path().c_str(),&opt);

	// mesh 列表
	for (int i = 0; i < HG_SceneCenter::inst().ref_meshList().size() ; i++)
	{
		HG_Mesh hg_mesh = HG_SceneCenter::inst().ref_meshList().at(i);
		EH_Mesh mesh;
		mesh.verts = (EH_Vec*)malloc(sizeof(EH_Vec) * hg_mesh.get_verts().size());
		mesh.normals = (EH_Vec*)malloc(sizeof(EH_Vec) * hg_mesh.get_verts().size());
		mesh.uvs = (EH_Vec2*)malloc(sizeof(EH_Vec2) * hg_mesh.get_verts().size());
		mesh.face_indices = (uint_t *)malloc(sizeof(uint_t) * hg_mesh.get_faces().size() * 3);

		storage.fill(mesh,hg_mesh);
		EH_add_mesh(storage.get_context(),hg_mesh.get_unique_code().c_str(),&mesh);

		free(mesh.verts);
		free(mesh.normals);
		free(mesh.uvs);
		free(mesh.face_indices);
	}

	// 材质 列表
// 	for (int i = 0; i < HG_SceneCenter::inst().ref_materialList().size() ; i++)
// 	{
// 		HG_Material hg_material = HG_SceneCenter::inst().ref_materialList().at(i);
// 		EH_Material material;
// 		storage.fill(material,hg_material);
// 		EH_add_material(storage.get_context(),hg_material.get_unique_code().c_str(),&material);
// 	}

	// mesh 实例 列表
	for (int i = 0; i < HG_SceneCenter::inst().ref_meshInstanceList().size() ; i++)
	{
		HG_MeshInstance hg_meshInst = HG_SceneCenter::inst().ref_meshInstanceList().at(i);
		EH_MeshInstance meshInst;
		storage.fill(meshInst,hg_meshInst);
		EH_add_mesh_instance(storage.get_context(),hg_meshInst.get_unique_code().c_str(),&meshInst);
	}

	
	//外部对象列表
	for (int i = 0; i < HG_SceneCenter::inst().ref_modelList().size() ; i++)
	{
		HG_ModelInstance hg_model = HG_SceneCenter::inst().ref_modelList().at(i);
		EH_AssemblyInstance model;
		storage.fill(model,hg_model);
		EH_add_assembly_instance(storage.get_context(),hg_model.get_unique_code().c_str(),&model);
	}
	
	//摄像机
	if (HG_SceneCenter::inst().get_cameraList().size() > 0)
	{
		EH_Camera camera;
		storage.fill(camera,HG_SceneCenter::inst().get_cameraList().at(0));
		EH_set_camera(storage.get_context(), &camera);
	}
	else
	{
		HGLOG_WARN("camera empty");
	}
	

	//阳光
	EH_Sun sun;
	storage.fill(sun,HG_SceneCenter::inst().get_sun());
	EH_set_sun(storage.get_context(),&sun);
	
	//天空
	EH_Sky sky;
	storage.fill(sky,HG_SceneCenter::inst().get_sky());
	EH_set_sky(storage.get_context(),&sky);


	EH_end_export(storage.get_context());

	storage.clearCharBuffer();
}

void RenderManager::Begin()
{
	CString runParam;
	runParam.Format("-resolution %d %d ",HG_SceneCenter::inst().get_param().get_render_width(),HG_SceneCenter::inst().get_param().get_render_height());

	CString showParam;
	showParam.Format("%s %s -display ",get_render_exe_path().c_str(),get_scene_path().c_str());

	CString endParam;
	endParam.Format("> D:\\debug.log");

	CString cmdRunRender;
	cmdRunRender = showParam + runParam + endParam ;
	system(cmdRunRender.GetBuffer());
}

