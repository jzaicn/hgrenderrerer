#pragma once
#include "afxwin.h"
#include "DialogPlus.h"
#include "resource.h"
// ImageSetting �Ի���

class DialogImageSettings : public DialogPlus
{
	DECLARE_DYNAMIC(DialogImageSettings)

public:
	DialogImageSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogImageSettings();

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

	afx_msg void OnBnClickedBeginBtn();
	afx_msg void OnBnClickedSettingBtn();
};
