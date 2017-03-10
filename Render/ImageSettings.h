#pragma once
#include "afxwin.h"
#include "DialogPlus.h"

// ImageSetting �Ի���

class ImageSettings : public DialogPlus
{
	DECLARE_DYNAMIC(ImageSettings)

public:
	ImageSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ImageSettings();

// �Ի�������
	enum { IDD = IDD_IMAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��Ⱦ����
	CComboBox m_RenderQuality;
	// ͼ���С
	CComboBox m_ImageSize;
	virtual BOOL OnInitDialog();

};
