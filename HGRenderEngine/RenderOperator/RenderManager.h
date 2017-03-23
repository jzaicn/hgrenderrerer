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
	// ����ͼ��
	void SaveImage(CString path);
	// ��ͼ��
	void LoadImage(CString path);
	// �˳�
	void Clear();
	// ����ͼ��ԭʼ�ߴ�
	void GetImageData();
	// ��������
	void OnSaveESS(CString path);
	// ��ȡ����
	void OnLoadESS(CString path);
	// ��Ⱦ��ʼ
	void OnBegin();
	// ��Ⱦֹͣ
	void OnStop();
	// ��Ⱦֹͣ
	void OnDone();
	// ��Ⱦ���ø���
	void OnSettingUpdate();

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
};

