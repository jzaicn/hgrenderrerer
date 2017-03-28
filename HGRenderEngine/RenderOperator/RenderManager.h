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
	// ����ͼ��
	void SaveImage(std::string path);
	// ��ͼ��
	void LoadImage(std::string path);
	
	// ����ͼ��ԭʼ�ߴ�
	void GetImageData();
	// ��������
	void SaveESS(std::string path, bool flag);

	void hg_test_ess_data();

	void ei_test_ess_data();

	// ��ȡ����
	void LoadESS(std::string path);
	// ��Ⱦ���ø���
	void SettingUpdate();


	// ��Ⱦ��ʼ
	void Begin();
	// ��Ⱦֹͣ
	void Stop();
	// ��Ⱦֹͣ
	void Done();
	// ��Ⱦ����
	void Clear();

	//TODO: ׼������
	//TODO: �����ع�
	//TODO: ��������
	//TODO: �������
	//TODO: ����б�
	//TODO: light
	//TODO: mesh
	//TODO: model
	//TODO: material
	//TODO: meshʵ��

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

