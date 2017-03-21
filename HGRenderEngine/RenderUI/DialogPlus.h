#pragma once


class DialogPlus :public CDialogEx
{
	DECLARE_DYNAMIC(DialogPlus)
public:
	typedef enum
	{
		RENDER_COMMAND_BEGIN = WM_USER,	//��Ⱦ����������ʼ

		RENDER_SAVE_IMAGE,	// ��ͼ��
		RENDER_LOAD_IMAGE,	// ����ͼ��
		RENDER_EXIT,	// �˳�
		RENDER_ZOOM_ORIGIN_IMAGE,	// ����ͼ��ԭʼ�ߴ�
		RENDER_ZOOM_FIT_IMAGE,	// ����ͼ����Ӧ����
		RENDER_ZOOM_IN_IMAGE,	// �Ŵ�ͼ��
		RENDER_ZOOM_OUT_IMAGE,	// ��Сͼ��
		RENDER_TOOLBAR_SHOW_HIDE,	// ������ ����/��ʾ
		RENDER_DISPLAY_SHOW_HIDE,	// ��ȾЧ������  ����/��ʾ
		RENDER_SETTINGS_SHOW_HIDE,	// ��Ⱦ����  ����/��ʾ
		RENDER_STATUS_SHOW_HIDE,	// ״̬��  ����/��ʾ
		RENDER_DEFAULT_LAYOUT,	// �ָ�Ĭ�ϲ��� 
		RENDER_SAVE_LAYOUT,	// ���沼�� 
		RENDER_LOAD_LAYOUT,	// �ָ����� 
		RENDER_HELP,	// ����
		RENDER_SAVE_SETTINGS,	// ��������
		RENDER_LOAD_SETTINGS,	// ��ȡ����
		RENDER_CHANGE_SETTINGS,	// ��������
		RENDER_BEGIN,	// ��Ⱦ��ʼ
		RENDER_STOP,	// ��Ⱦֹͣ
		RENDER_DONE,	// ��Ⱦֹͣ

		RENDER_COMMAND_END,	//��Ⱦ������������
	}CMD;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DialogPlus();
	DialogPlus(UINT nIDTemplate, CWnd *pParent = NULL);
	DialogPlus(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
	~DialogPlus(void);

//////////////////////////////////////////////////////////////////////////
// ���ܺ���
public:
	void SetBtnImage(int _btn_marco,int _res_marco);
	virtual void OnOK();
	virtual void OnCancel();
	CRect getOffset(UINT fwSide, LPRECT pRect);
	

	//////////////////////////////////////////////////////////////////////////
	// ��������
public:
	HWND ShareHwnd() const { return m_shareHwnd; }
	void ShareHwnd(HWND val) { m_shareHwnd = val; }

	CString SaveImagePath() const { return m_saveImagePath; }
	void SaveImagePath(CString val) { m_saveImagePath = val; }
private:
	static HWND m_shareHwnd;
	
	static CString m_saveImagePath;


};

