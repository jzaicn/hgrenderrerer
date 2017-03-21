
// RenderUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RenderUI.h"
#include "RenderUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRenderUIDlg 对话框




CRenderUIDlg::CRenderUIDlg(CWnd* pParent /*=NULL*/)
	: DialogPlus(CRenderUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenderUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRenderUIDlg, CDialog)
	ON_WM_MOVE()
	ON_WM_SIZING()

// 	ON_MESSAGE(RENDER_SAVE_IMAGE,&CRenderUIDlg::OnSaveImage)	// 打开图像
// 	ON_MESSAGE(RENDER_LOAD_IMAGE,&CRenderUIDlg::OnLoadImage)	// 保存图像
// 	ON_MESSAGE(RENDER_EXIT,&CRenderUIDlg::OnExit)	// 退出
// 	ON_MESSAGE(RENDER_ZOOM_ORIGIN_IMAGE,&CRenderUIDlg::OnZoomOriginImage)	// 缩放图像到原始尺寸
// 	ON_MESSAGE(RENDER_ZOOM_FIT_IMAGE,&CRenderUIDlg::OnZoomFitImage)	// 缩放图像到适应窗口
// 	ON_MESSAGE(RENDER_ZOOM_IN_IMAGE,&CRenderUIDlg::OnZoomInImage)	// 放大图像
// 	ON_MESSAGE(RENDER_ZOOM_OUT_IMAGE,&CRenderUIDlg::OnZoomOutImage)	// 缩小图像
// 	ON_MESSAGE(RENDER_TOOLBAR_SHOW_HIDE,&CRenderUIDlg::OnToolbarShowHide)	// 工具栏 隐藏/显示
// 	ON_MESSAGE(RENDER_DISPLAY_SHOW_HIDE,&CRenderUIDlg::OnDisplayShowHide)	// 渲染效果配置  隐藏/显示
// 	ON_MESSAGE(RENDER_STATUS_SHOW_HIDE,&CRenderUIDlg::OnStatusShowHide)	// 状态栏  隐藏/显示
// 	ON_MESSAGE(RENDER_DEFAULT_LAYOUT,&CRenderUIDlg::OnDefaultLayout)	// 恢复默认布局 
// 	ON_MESSAGE(RENDER_SAVE_LAYOUT,&CRenderUIDlg::OnSaveLayout)	// 保存布局 
// 	ON_MESSAGE(RENDER_LOAD_LAYOUT,&CRenderUIDlg::OnLoadLayout)	// 恢复布局 
// 	ON_MESSAGE(RENDER_HELP,&CRenderUIDlg::OnHelp)	// 帮助
// 	ON_MESSAGE(RENDER_SAVE_SETTINGS,&CRenderUIDlg::OnSaveSettings)	// 保存配置
// 	ON_MESSAGE(RENDER_LOAD_SETTINGS,&CRenderUIDlg::OnLoadSettings)	// 读取配置
// 	ON_MESSAGE(RENDER_BEGIN,&CRenderUIDlg::OnBegin)	// 渲染开始
// 	ON_MESSAGE(RENDER_STOP,&CRenderUIDlg::OnStop)	// 渲染停止
// 	ON_MESSAGE(RENDER_DONE,&CRenderUIDlg::OnDone)	// 渲染停止
ON_WM_SIZE()
END_MESSAGE_MAP()

//CRenderUIDlg 消息处理程序
UINT CRenderUIDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

// CRenderUIDlg 消息处理程序

BOOL CRenderUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// TODO: 在此添加额外的初始化代码
	//TODO: 这种写法有bug，在创建窗口，内部move的时候会报错
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

	m_oldRect = statusRect;
	m_newRect = statusRect;
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// void CRenderUIDlg::OnSizing(UINT fwSide, LPRECT pRect)
// {
// 	CRect offset = getOffset(fwSide,pRect);
// 	CDialog::OnSizing(fwSide, pRect);
// 
// // 	//移动图片窗口
// // 	m_displayResultDlgContainerRect.left += offset.left;
// // 	m_displayResultDlgContainerRect.right += offset.right;
// // 	m_displayResultDlgContainerRect.top += offset.top;
// // 	m_displayResultDlgContainerRect.bottom += offset.bottom;
// // 	GetDlgItem(IDC_DISPLAYRESULT_WIN)->MoveWindow(m_displayResultDlgContainerRect);
// // 	displayResultDlg.MoveWindow(0,0,m_displayResultDlgContainerRect.Width(),m_displayResultDlgContainerRect.Height());
// // 
// // 	//工具栏窗口
// // 	m_toolBarDlgContainerRect.left += offset.left;
// // 	m_toolBarDlgContainerRect.right += offset.right;
// // 	m_toolBarDlgContainerRect.top += offset.top;
// // 	m_toolBarDlgContainerRect.bottom += offset.top;
// // 	GetDlgItem(IDC_TOOLBAR_WIN)->MoveWindow(m_toolBarDlgContainerRect);
// // 
// // 	//移动图片窗口
// // 	m_imageSettingDlgContainerRect.left += offset.right;
// // 	m_imageSettingDlgContainerRect.right += offset.right;
// // 	m_imageSettingDlgContainerRect.top += offset.top;
// // 	m_imageSettingDlgContainerRect.bottom += offset.top;
// // 	GetDlgItem(IDC_IMAGE_WIN)->MoveWindow(m_imageSettingDlgContainerRect);
// // 
// // 	//移动属性窗口
// // 	m_paramSettingDlgContainerRect.left += offset.right;
// // 	m_paramSettingDlgContainerRect.right += offset.right;
// // 	m_paramSettingDlgContainerRect.top += offset.top;
// // 	m_paramSettingDlgContainerRect.bottom += offset.bottom;
// // 	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_paramSettingDlgContainerRect);
// // 
// // 
// // 	//移动状态栏
// // 	CRect statusRect;
// // 	GetClientRect(statusRect);
// // 	m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);
// // 	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_paramSettingDlgContainerRect.Width());
// // 	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_paramSettingDlgContainerRect.Width());
// 
// 	Invalidate(TRUE);
// }

void CRenderUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRenderUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRenderUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// #include "JsonCpp/json.h"
// #include <fstream>
// 
// void CRenderUIDlg::OnBnClickedOk()
// {
// 	std::ifstream  readstream("d:\\1.txt");
// 	if (readstream.is_open())
// 	{
// 		std::string text;
// 		readstream >> text ;
// 		readstream.close();
// 
// 		Json::Reader reader;
// 		Json::Value root;
// 		if (reader.parse(text,root))
// 		{
// 			MessageBox(root.toStyledString().c_str());
// 		}
// 	}
// 	
// 
// 
// 
// 	CDialogEx::OnOK();
// }
// 
// LRESULT CRenderUIDlg::OnSaveImage(WPARAM w,LPARAM l)
// {
// 	CString m_saveImagePath;
// 	//TODO: 
// 	//RenderManager::getInstance().saveImage(m_saveImagePath);
// 	return 0;
// }
// 
// LRESULT CRenderUIDlg::OnBegin(WPARAM w,LPARAM l)
// {
// //TODO: 
// 	//RenderManager::getInstance().startRenderCore();
// 
// 
// 	return 0;
// }


void CRenderUIDlg::OnBnClickedButton1()
{
	DisplayResult dlg;
	dlg.DoModal();
}


void CRenderUIDlg::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
	GetClientRect(m_newRect);

	CRect offset = CRect(
		m_newRect.left - m_oldRect.left,
		m_newRect.top - m_oldRect.top,
		m_newRect.right - m_oldRect.right,
		m_newRect.bottom - m_oldRect.bottom
	);
	
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



}
