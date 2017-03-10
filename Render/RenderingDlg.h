#pragma once
#include "resource.h"
// RenderingDlg 对话框
#include "DialogPlus.h"
#include "RenderSettings.h"
#include "ImageSettings.h"
#include "RenderToolBar.h"
#include "DisplayResult.h"


class RenderingDlg : public DialogPlus
{
	DECLARE_DYNAMIC(RenderingDlg)

public:
	RenderingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RenderingDlg();

// 对话框数据
	enum { IDD = IDD_RENDERINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:	
	CScrollBar m_settingScroll;				// 子窗口滚动条


	DisplayResult displayResultDlg;				// 绘图对话框
	CRect m_displayResultDlgRect;				// 绘图对话框区域
	CRect m_displayResultDlgContainerRect;		// 绘图包围区域

	RenderToolBar toolBarDlg;				// 工具栏对话框
	CRect m_toolBarDlgRect;					// 工具栏对话框区域
	CRect m_toolBarDlgContainerRect;		// 工具栏包围区域


	ImageSettings imageSettingDlg;			// 图片配置对话框
	CRect m_imageSettingDlgRect;			// 图片配置对话框区域
	CRect m_imageSettingDlgContainerRect;	// 图片配置包围区域


	RenderSettings paramSettingDlg;			// 属性配置对话框
	CRect m_paramSettingDlgRect;			// 属性配置对话框区域
	CRect m_paramSettingDlgContainerRect;	// 属性配置包围区域



	static UINT indicators[];				//状态栏文字
	CStatusBar   m_wndStatusBar;			//状态栏
	
	
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	void OnCancel()	{	CDialogEx::OnCancel();	};
};
