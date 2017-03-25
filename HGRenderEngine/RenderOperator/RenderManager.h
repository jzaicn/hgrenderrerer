#pragma once

#include <string>
#include "HG_BaseModel.h"


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
	// �˳�
	void Clear();
	// ����ͼ��ԭʼ�ߴ�
	void GetImageData();
	// ��������
	void SaveESS(std::string path);
	// ��ȡ����
	void LoadESS(std::string path);
	// ��Ⱦ��ʼ
	void Begin();
	// ��Ⱦֹͣ
	void Stop();
	// ��Ⱦֹͣ
	void Done();
	// ��Ⱦ���ø���
	void SettingUpdate();

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

	void initial();
	

private:
	class DataStorageCore;
	static DataStorageCore storage;
	class CallBackCore;
	static CallBackCore callback;



public:
	GETSET(std::string,render_exe_path);
	GETSET(std::string,scene_path);
};

