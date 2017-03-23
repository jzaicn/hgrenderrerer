#pragma once
class RenderManager
{
private:
	RenderManager(void);
	~RenderManager(void);

	static RenderManager manager;
	
public:
	RenderManager& inst();

public:
	// 保存图像
	void SaveImage(CString path);
	// 打开图像
	void LoadImage(CString path);
	// 退出
	void Clear();
	// 缩放图像到原始尺寸
	void GetImageData();
	// 保存配置
	void OnSaveESS(CString path);
	// 读取配置
	void OnLoadESS(CString path);
	// 渲染开始
	void OnBegin();
	// 渲染停止
	void OnStop();
	// 渲染停止
	void OnDone();
	// 渲染设置更新
	void OnSettingUpdate();

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
};

