#pragma once
#include "resource.h"
// RenderingDlg 对话框
#include "RenderSettings.h"

class RenderingDlg : public CDialog
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
	CRect m_settingDlgContainerRect;		// 子窗口包围区域
	CRect m_settingDlgRect;					// 子窗口对话框区域
	RenderSettings settingDlg;				// 属性配置对话框

	static UINT indicators[];				//状态栏文字
	CStatusBar   m_wndStatusBar;			//状态栏
	
	CToolBar m_wndToolbar;
	
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
