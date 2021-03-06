#pragma once
#include "afxwin.h"
#include "DialogPlus.h"
#include "resource.h"
// ImageSetting 对话框

#include "HG_RenderParam.h"

class DialogImageSettings : public DialogPlus
{
	DECLARE_DYNAMIC(DialogImageSettings)

public:
	DialogImageSettings(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogImageSettings();

// 对话框数据
	enum { IDD = IDD_IMAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 渲染质量对应的值
	std::vector<int> m_RenderQualityValue;
	// 渲染质量
	CComboBox m_RenderQuality;
	// 图像大小
	CComboBox m_ImageSize;
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBeginBtn();
	afx_msg void OnBnClickedSettingBtn();

	HG_RenderParam get_RenderParam();
	void set_RenderParam(HG_RenderParam param);
	int findQualityCurSelByValue(int val);
};
