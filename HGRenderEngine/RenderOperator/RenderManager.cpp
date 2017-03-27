#include "StdAfx.h"
#include "RenderManager.h"
#include "HG_SceneCenter.h"
#include "Elara/ElaraHomeAPI.h"
#include "HgLog/HgLog.h"
#include "HGCode.h"
#include "DialogPlus.h"

using namespace Gdiplus;


//////////////////////////////////////////////////////////////////////////
// 数据存储核心
class RenderManager::DataStorageCore
{
public:
	DataStorageCore(){set_context(NULL);}
	~DataStorageCore(){	clear();}
	void clear(){if (get_context())	{EH_delete(get_context());set_context(NULL);}}
	void init(){clear();initWhenNot();}
	bool initWhenNot(){if (!get_context()){set_context(EH_create());return true;}return false;}

private:
	GETSET(EH_Context*,context);

//////////////////////////////////////////////////////////////////////////
// 字符管理工具
#if 1
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
#endif

//////////////////////////////////////////////////////////////////////////
// 填充器
#if 1
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

#endif

};
//////////////////////////////////////////////////////////////////////////
// 回调函数响应中心
class RenderManager::CallBackCore
{

public:
	CallBackCore(){m_bool = true; }
	~CallBackCore(){}
	
	static bool m_bool;

//////////////////////////////////////////////////////////////////////////
// 回调函数
#if 1
public:
	static void dispaly_callback(uint_t ei_width, uint_t ei_height,const EH_RGBA *ei_image)
	{
		HGLOG_DEBUG("dispaly_callback");

		int mfc_width = ei_width;
		int mfc_height = ei_height;
		CRect rcDrawArea(0,0,mfc_width,mfc_height);
		Bitmap* m_pImg = ::new Bitmap(rcDrawArea.Width(), rcDrawArea.Height());
		//渲染传递过来的图片坐标系是数学坐标系，我们显示的是屏幕坐标
		//   y+↑                   十一→ x+
		//     丨                   丨
		//     十一→ x+            ↓ y+      
		if (m_bool)
		{
			//HGLOG_DEBUG("-------------------------------------------");
			int ei_index = 0;

			for (int ei_h = 0; ei_h < ei_height ; ei_h++)
			{
				for (int ei_w = 0; ei_w < ei_width ; ei_w++)
				{
					//按行从最底下获取图片
					int r = (int)(ei_image[ei_w + ei_index][0] * 255.0);				
					int g = (int)(ei_image[ei_w + ei_index][1] * 255.0);
					int b = (int)(ei_image[ei_w + ei_index][2] * 255.0);
					int a = (int)(ei_image[ei_w + ei_index][3] * 255.0);

					//HGLOG_DEBUG("color : ( %d , %d , %d, %d )",r,g,b,a);
					Color color(a,b,g,r);

					//mfc 按屏幕位置，从图片底部赋值
					m_pImg->SetPixel(ei_w,mfc_height-ei_h,color);
				}
				ei_index += ei_width;
			}
			//HGLOG_DEBUG("==========================================");

		}
		DialogPlus::Send(DialogPlus::RENDER_IMAGE_UPDATE,NULL,(LPARAM)m_pImg);
	}
	static void log_callback(EH_Severity severity, const char *msg)
	{
		HGLOG_DEBUG("log_callback level:%d , msg: %s ",(int)severity , msg);
	}
	static bool progress_callback(float progress)
	{
		HGLOG_DEBUG("progress_callback : %f ",progress);
		DialogPlus::Post(DialogPlus::RENDER_STATUS_UPDATE,DialogPlus::update_process,DialogPlus::getAccuracyInt(progress));
		return true;
	}
#endif
};
bool RenderManager::CallBackCore::m_bool = false;
//////////////////////////////////////////////////////////////////////////
// 渲染工作线程
class RenderWorkThread : public CWinThread
{
	DECLARE_DYNCREATE(RenderWorkThread)

public:
	RenderWorkThread(){};           // 动态创建所使用的受保护的构造函数
	virtual ~RenderWorkThread(){};

private:
	GETSET(std::string,scenePath);
	GETSET(EH_Context*,context);

public:
	virtual BOOL InitInstance()	
	{
		DialogPlus::Post(DialogPlus::RENDER_BEGIN);
		return TRUE;
	}
	virtual int ExitInstance() 
	{
		DialogPlus::Post(DialogPlus::RENDER_DONE);
		return CWinThread::ExitInstance();
	};
	bool checkRunable()
	{
		if (get_scenePath().empty())
		{
			HGLOG_DEBUG("场景路径空");
			return false;
		}
		if (!get_context())
		{
			HGLOG_DEBUG("渲染核心不存在");
			return false;
		}
		return true;
		
	}
	virtual int Run() 
	{	
		if (checkRunable())
		{
			EH_start_render(m_context,m_scenePath.c_str(),false);
		}
		return true;
	}
protected:
	DECLARE_MESSAGE_MAP()
};
IMPLEMENT_DYNCREATE(RenderWorkThread, CWinThread)
BEGIN_MESSAGE_MAP(RenderWorkThread, CWinThread)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// 数据实例
RenderManager RenderManager::manager;
RenderManager::DataStorageCore RenderManager::storage;
RenderManager::CallBackCore RenderManager::callback;
RenderWorkThread* RenderManager::renderThread = NULL;


RenderManager::RenderManager(void)
{
	set_render_exe_path("E:\\HGRENDER\\Elara_SDK_1_0_76\\bin\\er.exe");
	set_scene_path("D:\\my_scene.ess");
	renderThread = nullptr;
	
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
	if (storage.initWhenNot())
	{
		initial();
	}

	EH_ExportOptions option;
	option.base85_encoding = false;
	option.left_handed = true;
	EH_begin_export(storage.get_context(), "D:\\my_scene.ess", &option);

	EH_RenderOptions render_op;
	render_op.quality = EH_MEDIUM;
	EH_set_render_options(storage.get_context(), &render_op);

	//create cam
	EH_Camera cam;
	cam.fov = 45;
	cam.near_clip = 0.01f;
	cam.far_clip = 1000.0f;
	cam.image_width = 640;
	cam.image_height = 480;
	HG_Mat cam_tran = HG_Mat(
		HG_Vec4(0.731353, -0.681999, -0.0, 0.0),
		HG_Vec4(0.255481, 0.27397, 0.927184, 0.0),
		HG_Vec4(-0.632338, -0.678099, 0.374607, 0.0),
		HG_Vec4(-38.681263, -49.142731, 21.895681, 1.0)
	);
	storage.fill(cam.view_to_world,cam_tran);
	EH_set_camera(storage.get_context(), &cam);

	const char *mesh_name = "simple_mesh";
	EH_Mesh simple_mesh;
	float vertices[48] = {-8.5f, 0.0f, 8.5f,   8.5f, 0.0f, 8.5f,   8.5f, 8.0f, 8.5f,  -8.5f, 8.0f, 8.5f,
		-8.5f, 8.0f, -8.5f,  8.5f, 8.0f, -8.5f,  8.5f, 0.0f, -8.5f, -8.5f, 0.0f, -8.5f,
		8.5f, 0.0f, 8.5f,   8.5f, 0.0f, -8.5f,  8.5f, 8.0f, -8.5f,  8.5f, 8.0f, 8.5f,
		-8.5f, 0.0f, -8.5f,  -8.5f, 0.0f, 8.5f,  -8.5f, 8.0f, 8.5f, -8.5f, 8.0f, -8.5f
	};
	float uvs[32] = {
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0
	};
	uint_t indice[36] = {
		0,2,1,
		0,3,2,

		1,2,6,
		6,5,1,

		4,5,6,
		6,7,4,

		2,3,6,
		6,3,7,

		0,7,3,
		0,4,7,

		0,1,5,
		0,5,4
	};
	simple_mesh.num_verts = 16;
	simple_mesh.num_faces = 12;
	simple_mesh.verts = (EH_Vec*)vertices;
	simple_mesh.face_indices = (uint_t*)indice;
	simple_mesh.uvs = (EH_Vec2*)uvs;
	EH_add_mesh(storage.get_context(), mesh_name, &simple_mesh);

	const char *simple_mtl = "simple_mtl";
	EH_Material simple_mat;
	float diff[3] = {1, 0, 0};
	memcpy(simple_mat.diffuse_color, diff, sizeof(EH_RGB));
	EH_add_material(storage.get_context(), simple_mtl, &simple_mat);		

	EH_Sun sun;
	sun.dir[0] = 0;
	sun.dir[1] = 0;
	float color[3] = {1, 1, 1};
	memcpy(sun.color, color, sizeof(color));
	sun.intensity = 200;
	EH_set_sun(storage.get_context(), &sun);

	const char *simple_inst_name = "simple_inst_name";
	EH_MeshInstance inst;
	inst.mesh_name = mesh_name;
	inst.mtl_name = simple_mtl;
	HG_Mat inst_tran = HG_Mat(
		HG_Vec4(1, 0, 0, 0),
		HG_Vec4(0, 1, 0, 0),
		HG_Vec4(0, 0, 1, 0),
		HG_Vec4(0, 0, 0, 1)
	);
	storage.fill(inst.mesh_to_world,inst_tran); 
	EH_add_mesh_instance(storage.get_context(), simple_inst_name, &inst);

	EH_AssemblyInstance include_inst;
	include_inst.filename = "D:\\default.ess";
	storage.fill(include_inst.mesh_to_world,inst_tran); 
	EH_add_assembly_instance(storage.get_context(), "include_test_ess",&include_inst);
	EH_end_export(storage.get_context());










// 	set_scene_path(path);
// 	
// 	storage.initWhenNot();
// 
// 	EH_ExportOptions opt;
// 	opt.base85_encoding = true;
// 	opt.left_handed = false;
// 
// 	EH_begin_export(storage.get_context(),get_scene_path().c_str(),&opt);
// 
// 	// mesh 列表
// 	for (int i = 0; i < HG_SceneCenter::inst().ref_meshList().size() ; i++)
// 	{
// 		HG_Mesh hg_mesh = HG_SceneCenter::inst().ref_meshList().at(i);
// 		EH_Mesh mesh;
// 		mesh.verts = (EH_Vec*)malloc(sizeof(EH_Vec) * hg_mesh.get_verts().size());
// 		mesh.normals = (EH_Vec*)malloc(sizeof(EH_Vec) * hg_mesh.get_verts().size());
// 		mesh.uvs = (EH_Vec2*)malloc(sizeof(EH_Vec2) * hg_mesh.get_verts().size());
// 		mesh.face_indices = (uint_t *)malloc(sizeof(uint_t) * hg_mesh.get_faces().size() * 3);
// 
// 		storage.fill(mesh,hg_mesh);
// 		EH_add_mesh(storage.get_context(),hg_mesh.get_unique_code().c_str(),&mesh);
// 
// 		free(mesh.verts);
// 		free(mesh.normals);
// 		free(mesh.uvs);
// 		free(mesh.face_indices);
// 	}
// 
// 	// 材质 列表
// // 	for (int i = 0; i < HG_SceneCenter::inst().ref_materialList().size() ; i++)
// // 	{
// // 		HG_Material hg_material = HG_SceneCenter::inst().ref_materialList().at(i);
// // 		EH_Material material;
// // 		storage.fill(material,hg_material);
// // 		EH_add_material(storage.get_context(),hg_material.get_unique_code().c_str(),&material);
// // 	}
// 
// 	// mesh 实例 列表
// 	for (int i = 0; i < HG_SceneCenter::inst().ref_meshInstanceList().size() ; i++)
// 	{
// 		HG_MeshInstance hg_meshInst = HG_SceneCenter::inst().ref_meshInstanceList().at(i);
// 		EH_MeshInstance meshInst;
// 		storage.fill(meshInst,hg_meshInst);
// 		EH_add_mesh_instance(storage.get_context(),hg_meshInst.get_unique_code().c_str(),&meshInst);
// 	}
// 
// 	
// 	//外部对象列表
// 	for (int i = 0; i < HG_SceneCenter::inst().ref_modelList().size() ; i++)
// 	{
// 		HG_ModelInstance hg_model = HG_SceneCenter::inst().ref_modelList().at(i);
// 		EH_AssemblyInstance model;
// 		storage.fill(model,hg_model);
// 		EH_add_assembly_instance(storage.get_context(),hg_model.get_unique_code().c_str(),&model);
// 	}
// 	
// 	//摄像机
// 	if (HG_SceneCenter::inst().get_cameraList().size() > 0)
// 	{
// 		EH_Camera camera;
// 		storage.fill(camera,HG_SceneCenter::inst().get_cameraList().at(0));
// 		EH_set_camera(storage.get_context(), &camera);
// 	}
// 	else
// 	{
// 		HGLOG_WARN("camera empty");
// 	}
// 	
// 
// 	//阳光
// 	EH_Sun sun;
// 	storage.fill(sun,HG_SceneCenter::inst().get_sun());
// 	EH_set_sun(storage.get_context(),&sun);
// 	
// 	//天空
// 	EH_Sky sky;
// 	storage.fill(sky,HG_SceneCenter::inst().get_sky());
// 	EH_set_sky(storage.get_context(),&sky);
// 
// 
// 	EH_end_export(storage.get_context());
// 
// 	storage.clearCharBuffer();
}



void RenderManager::SettingUpdate()
{
	HG_SceneCenter::inst().get_exposure();
}

void RenderManager::initial()
{
	EH_set_log_callback(storage.get_context(),callback.log_callback);
	EH_set_progress_callback(storage.get_context(),callback.progress_callback);
	EH_set_display_callback(storage.get_context(),callback.dispaly_callback);
}


void RenderManager::Begin()
{	
	DialogPlus::setStatusText(_T("开始渲染"));
	HGLOG_DEBUG("开始渲染");
	if (storage.initWhenNot())
	{
		initial();
	}
	if (!renderThread)
	{
		renderThread = new RenderWorkThread();
		renderThread->CreateThread(CREATE_SUSPENDED);
		renderThread->set_context(storage.get_context());
		renderThread->set_scenePath(get_scene_path());
		renderThread->ResumeThread();					//运行
	}
}

void RenderManager::Stop()
{
	HGLOG_DEBUG("RenderManager::Stop");
	Clear();
}

void RenderManager::Done()
{
	HGLOG_DEBUG("RenderManager::Done");
	Clear();
}

void RenderManager::Clear()
{
	HGLOG_DEBUG("RenderManager::Clear");
	if (renderThread)
	{
		renderThread->SuspendThread();
		delete renderThread;
	}
}
