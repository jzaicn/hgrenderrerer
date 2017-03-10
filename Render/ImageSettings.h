#pragma once
#include "afxwin.h"
#include "DialogPlus.h"

// ImageSetting 对话框

class ImageSettings : public DialogPlus
{
	DECLARE_DYNAMIC(ImageSettings)

public:
	ImageSettings(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ImageSettings();

// 对话框数据
	enum { IDD = IDD_IMAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 渲染质量
	CComboBox m_RenderQuality;
	// 图像大小
	CComboBox m_ImageSize;
	virtual BOOL OnInitDialog();

};
