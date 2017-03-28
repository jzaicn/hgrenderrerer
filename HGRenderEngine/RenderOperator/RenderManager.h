#pragma once

#include <string>
#include "HG_BaseModel.h"


class RenderWorkThread;
class RenderManager
{
private:
	RenderManager(void);
	~RenderManager(void);

	static RenderManager manager;
	
public:
	static RenderManager& inst();

public:
	// 保存图像
	void SaveImage(std::string path);
	// 打开图像
	void LoadImage(std::string path);
	
	// 缩放图像到原始尺寸
	void GetImageData();
	// 保存配置
	void SaveESS(std::string path, bool flag);

	void hg_test_ess_data();

	void ei_test_ess_data();

	// 读取配置
	void LoadESS(std::string path);
	// 渲染设置更新
	void SettingUpdate();


	// 渲染开始
	void Begin();
	// 渲染停止
	void Stop();
	// 渲染停止
	void Done();
	// 渲染清理
	void Clear();

	//TODO: 准备数据
	//TODO: 更新曝光
	//TODO: 更新阳光
	//TODO: 更新天空
	//TODO: 相机列表
	//TODO: light
	//TODO: mesh
	//TODO: model
	//TODO: material
	//TODO: mesh实例

	void initWhenNot();
	

private:
	class DataStorageCore;
	static DataStorageCore storage;
	class CallBackCore;
	static CallBackCore callback;
	static RenderWorkThread* renderThread;


public:
	GETSET(std::string,render_exe_path);
	GETSET(std::string,scene_path);
};

