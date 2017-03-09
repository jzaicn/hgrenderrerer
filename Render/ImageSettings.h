#pragma once
#include "afxwin.h"


// ImageSetting �Ի���

class ImageSettings : public CDialogEx
{
	DECLARE_DYNAMIC(ImageSettings)

public:
	ImageSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ImageSettings();

// �Ի�������
	enum { IDD = IDD_IMAGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��Ⱦ����
	CComboBox m_RenderQuality;
	// ͼ���С
	CComboBox m_ImageSize;
	virtual BOOL OnInitDialog();

	void SetBtnImage(int _btn_marco,int _res_marco);

	virtual void OnOK();
	virtual void OnCancel();
};
