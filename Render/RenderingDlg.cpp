// RenderingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "RenderingDlg.h"
#include "afxdialogex.h"
#include "RenderManager.h"


#pragma comment(lib,"HgLog.lib")
#pragma comment(lib,"log4cpp.lib")

// RenderingDlg 对话框

IMPLEMENT_DYNAMIC(RenderingDlg, CDialog)

RenderingDlg::RenderingDlg(CWnd* pParent /*=NULL*/)
	: DialogPlus(RenderingDlg::IDD, pParent)
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
	
	ON_MESSAGE(RENDER_SAVE_IMAGE,&RenderingDlg::OnSaveImage)	// 打开图像
	ON_MESSAGE(RENDER_LOAD_IMAGE,&RenderingDlg::OnLoadImage)	// 保存图像
	ON_MESSAGE(RENDER_EXIT,&RenderingDlg::OnExit)	// 退出
	ON_MESSAGE(RENDER_ZOOM_ORIGIN_IMAGE,&RenderingDlg::OnZoomOriginImage)	// 缩放图像到原始尺寸
	ON_MESSAGE(RENDER_ZOOM_FIT_IMAGE,&RenderingDlg::OnZoomFitImage)	// 缩放图像到适应窗口
	ON_MESSAGE(RENDER_ZOOM_IN_IMAGE,&RenderingDlg::OnZoomInImage)	// 放大图像
	ON_MESSAGE(RENDER_ZOOM_OUT_IMAGE,&RenderingDlg::OnZoomOutImage)	// 缩小图像
	ON_MESSAGE(RENDER_TOOLBAR_SHOW_HIDE,&RenderingDlg::OnToolbarShowHide)	// 工具栏 隐藏/显示
	ON_MESSAGE(RENDER_DISPLAY_SHOW_HIDE,&RenderingDlg::OnDisplayShowHide)	// 渲染效果配置  隐藏/显示
	ON_MESSAGE(RENDER_STATUS_SHOW_HIDE,&RenderingDlg::OnStatusShowHide)	// 状态栏  隐藏/显示
	ON_MESSAGE(RENDER_DEFAULT_LAYOUT,&RenderingDlg::OnDefaultLayout)	// 恢复默认布局 
	ON_MESSAGE(RENDER_SAVE_LAYOUT,&RenderingDlg::OnSaveLayout)	// 保存布局 
	ON_MESSAGE(RENDER_LOAD_LAYOUT,&RenderingDlg::OnLoadLayout)	// 恢复布局 
	ON_MESSAGE(RENDER_HELP,&RenderingDlg::OnHelp)	// 帮助
	ON_MESSAGE(RENDER_SAVE_SETTINGS,&RenderingDlg::OnSaveSettings)	// 保存配置
	ON_MESSAGE(RENDER_LOAD_SETTINGS,&RenderingDlg::OnLoadSettings)	// 读取配置
	ON_MESSAGE(RENDER_BEGIN,&RenderingDlg::OnBegin)	// 渲染开始
	ON_MESSAGE(RENDER_STOP,&RenderingDlg::OnStop)	// 渲染停止
	ON_MESSAGE(RENDER_DONE,&RenderingDlg::OnDone)	// 渲染停止
END_MESSAGE_MAP()


// RenderingDlg 消息处理程序
UINT RenderingDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

BOOL RenderingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	HgLog::HgLog::initDebugLogCategory();
	ShareHwnd(m_hWnd);
	afxAmbientActCtx = FALSE;

	// 绘图对话框
	displayResultDlg.Create(IDD_DISPLAY_DLG,GetDlgItem(IDC_DISPLAYRESULT_WIN));
	displayResultDlg.ShowWindow(SW_SHOW);
	displayResultDlg.GetWindowRect(m_toolBarDlgRect);
	GetDlgItem(IDC_DISPLAYRESULT_WIN)->GetWindowRect(m_displayResultDlgContainerRect);
	ScreenToClient(m_displayResultDlgContainerRect);

	// 工具栏对话框
	toolBarDlg.Create(IDD_TOOLBAR_DLG,GetDlgItem(IDC_TOOLBAR_WIN));
	toolBarDlg.ShowWindow(SW_SHOW);
	toolBarDlg.GetWindowRect(m_toolBarDlgRect);
	GetDlgItem(IDC_TOOLBAR_WIN)->GetWindowRect(m_toolBarDlgContainerRect);
	ScreenToClient(m_toolBarDlgContainerRect);

	// 图片对话框
	imageSettingDlg.Create(IDD_IMAGE_DLG,GetDlgItem(IDC_IMAGE_WIN));
	imageSettingDlg.ShowWindow(SW_SHOW);
	imageSettingDlg.GetWindowRect(m_imageSettingDlgRect);
	GetDlgItem(IDC_IMAGE_WIN)->GetWindowRect(m_imageSettingDlgContainerRect);
	ScreenToClient(m_imageSettingDlgContainerRect);

	// 设置参数对话框
	paramSettingDlg.Create(IDD_SETTINGDLG,GetDlgItem(IDC_SETTING_WIN));
	paramSettingDlg.ShowWindow(SW_SHOW);
	paramSettingDlg.GetWindowRect(m_paramSettingDlgRect);
	GetDlgItem(IDC_SETTING_WIN)->GetWindowRect(m_paramSettingDlgContainerRect);
	ScreenToClient(m_paramSettingDlgContainerRect);


	//创建状态栏
	CRect statusRect;
    GetClientRect(statusRect);
    if(!m_wndStatusBar.Create(this)|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))) return false;
    m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);// 调整状态栏的位置和大小
	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_paramSettingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_paramSettingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneText(0,"准备就绪");
	m_wndStatusBar.SetPaneText(1,"当前缩放比：100%");

	return TRUE; 
}


void RenderingDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CRect offset = getOffset(fwSide,pRect);
	CDialog::OnSizing(fwSide, pRect);
	
	//移动图片窗口
	m_displayResultDlgContainerRect.left += offset.left;
	m_displayResultDlgContainerRect.right += offset.right;
	m_displayResultDlgContainerRect.top += offset.top;
	m_displayResultDlgContainerRect.bottom += offset.bottom;
	GetDlgItem(IDC_DISPLAYRESULT_WIN)->MoveWindow(m_displayResultDlgContainerRect);
	displayResultDlg.MoveWindow(0,0,m_displayResultDlgContainerRect.Width(),m_displayResultDlgContainerRect.Height());

	//工具栏窗口
	m_toolBarDlgContainerRect.left += offset.left;
	m_toolBarDlgContainerRect.right += offset.right;
	m_toolBarDlgContainerRect.top += offset.top;
	m_toolBarDlgContainerRect.bottom += offset.top;
	GetDlgItem(IDC_TOOLBAR_WIN)->MoveWindow(m_toolBarDlgContainerRect);

	//移动图片窗口
	m_imageSettingDlgContainerRect.left += offset.right;
	m_imageSettingDlgContainerRect.right += offset.right;
	m_imageSettingDlgContainerRect.top += offset.top;
	m_imageSettingDlgContainerRect.bottom += offset.top;
	GetDlgItem(IDC_IMAGE_WIN)->MoveWindow(m_imageSettingDlgContainerRect);

	//移动属性窗口
	m_paramSettingDlgContainerRect.left += offset.right;
	m_paramSettingDlgContainerRect.right += offset.right;
	m_paramSettingDlgContainerRect.top += offset.top;
	m_paramSettingDlgContainerRect.bottom += offset.bottom;
	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_paramSettingDlgContainerRect);


	//移动状态栏
	CRect statusRect;
    GetClientRect(statusRect);
	m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);
	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_paramSettingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_paramSettingDlgContainerRect.Width());

	Invalidate(TRUE);
}

LRESULT RenderingDlg::OnSaveImage(WPARAM w,LPARAM l)
{
	CString m_saveImagePath;
	RenderManager::getInstance().saveImage(m_saveImagePath);
	return 0;
}

LRESULT RenderingDlg::OnBegin(WPARAM w,LPARAM l)
{
	//RenderManager::getInstance();


	return 0;
}

