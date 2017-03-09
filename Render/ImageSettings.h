#pragma once
#include "afxwin.h"


// ImageSetting 对话框

class ImageSettings : public CDialogEx
{
	DECLARE_DYNAMIC(ImageSettings)

public:
	ImageSettings(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ImageSettings();

// 对话框数据
	enum { IDD = IDD_IMAGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 渲染质量
	CComboBox m_RenderQuality;
	// 图像大小
	CComboBox m_ImageSize;
	virtual BOOL OnInitDialog();

	void SetBtnImage(int _btn_marco,int _res_marco);

	virtual void OnOK();
	virtual void OnCancel();
};
