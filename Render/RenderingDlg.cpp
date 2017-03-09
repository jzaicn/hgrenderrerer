// RenderingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "RenderingDlg.h"
#include "afxdialogex.h"


// RenderingDlg 对话框

IMPLEMENT_DYNAMIC(RenderingDlg, CDialog)

RenderingDlg::RenderingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RenderingDlg::IDD, pParent)
{
}

RenderingDlg::~RenderingDlg()
{
}

void RenderingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RenderingDlg, CDialog)
	ON_WM_MOVE()
	ON_WM_SIZING()
	
	//工具栏
// 	ON_COMMAND(TB_SAVE, &RenderingDlg::OnSave)						//保存
// 	ON_COMMAND(TB_ZOOM_ORIGIN, &RenderingDlg::OnZoomOrigin)			//1:1分辨率
// 	ON_COMMAND(TB_ZOOM_FIT, &RenderingDlg::OnZoomFit)				//适配
END_MESSAGE_MAP()


// RenderingDlg 消息处理程序
UINT RenderingDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

BOOL RenderingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	afxAmbientActCtx = FALSE;

	// 绑定设置子窗口
	paramSettingDlg.Create(IDD_SETTINGDLG,GetDlgItem(IDC_SETTING_WIN));
	paramSettingDlg.ShowWindow(SW_SHOW);
	paramSettingDlg.GetWindowRect(m_settingDlgRect);
	
	//修改设置窗口位置
	GetDlgItem(IDC_SETTING_WIN)->GetWindowRect(m_settingDlgContainerRect);
	ScreenToClient(m_settingDlgContainerRect);
	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_settingDlgContainerRect);

	//图片属性设置窗口
	imageSettingDlg.Create(IDD_IMAGEDLG,GetDlgItem(IDC_IMAGE_SETTINGS));
	imageSettingDlg.ShowWindow(SW_SHOW);
	imageSettingDlg.GetWindowRect(m_imageDlgRect);
	GetDlgItem(IDC_IMAGE_SETTINGS)->GetWindowRect(m_imageDlgContainerRect);
	ScreenToClient(m_imageDlgContainerRect);
	GetDlgItem(IDC_IMAGE_SETTINGS)->MoveWindow(m_imageDlgContainerRect);


	//创建状态栏
	CRect statusRect;
    GetClientRect(statusRect);
    if(!m_wndStatusBar.Create(this)|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))) return false;
    m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);// 调整状态栏的位置和大小
	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_settingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_settingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneText(0,"准备就绪");
	m_wndStatusBar.SetPaneText(1,"当前缩放比：100%");

	return TRUE; 
}


void RenderingDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CRect winrect;
	GetWindowRect(winrect);
	CDialog::OnSizing(fwSide, pRect);
	CRect rect(pRect->left,pRect->top,pRect->left,pRect->bottom);
	
	CRect offset(0,0,0,0);
	offset.left = pRect->left - winrect.left;
	offset.right = pRect->right - winrect.right;
	offset.top = pRect->top - winrect.top;
	offset.bottom = pRect->bottom - winrect.bottom;
	


	//移动属性窗口
	m_settingDlgContainerRect.left += offset.right;
	m_settingDlgContainerRect.right += offset.right;
	m_settingDlgContainerRect.top += offset.top;
	m_settingDlgContainerRect.bottom += offset.bottom;
	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_settingDlgContainerRect);

	//移动图片窗口
	m_imageDlgContainerRect.left += offset.right;
	m_imageDlgContainerRect.right += offset.right;
	m_imageDlgContainerRect.top += offset.top;
	m_imageDlgContainerRect.bottom += offset.top;
	GetDlgItem(IDC_IMAGE_SETTINGS)->MoveWindow(m_imageDlgContainerRect);

	//移动状态栏
	CRect statusRect;
    GetClientRect(statusRect);
	m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);
	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_settingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_settingDlgContainerRect.Width());

	Invalidate(TRUE);
}

void RenderingDlg::OnSave()
{
	MessageBox("OnSave");
}

void RenderingDlg::OnZoomOrigin()
{
	MessageBox("OnZoomOrigin");
}

void RenderingDlg::OnZoomFit()
{
	MessageBox("OnZoomFit");
}
