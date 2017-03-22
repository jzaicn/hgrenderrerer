
// RenderOperatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RenderOperator.h"
#include "RenderOperatorDlg.h"
#include "afxdialogex.h"
#include "JsonCpp/json.h"
#include <fstream>
#include "HgLog/HgLog.h"
#include "HG_SceneCenter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#if 1

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
#endif // 1

//////////////////////////////////////////////////////////////////////////
// CRenderOperatorDlg 对话框

UINT CRenderOperatorDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};


CRenderOperatorDlg::CRenderOperatorDlg(CWnd* pParent /*=NULL*/)
	: DialogPlus(CRenderOperatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenderOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	DialogPlus::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRenderOperatorDlg, DialogPlus)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRenderOperatorDlg 消息处理程序

BOOL CRenderOperatorDlg::OnInitDialog()
{
	DialogPlus::OnInitDialog();
	HgLog::HgLog::initDebugLogCategory();

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
 	paramSettingDlg.Create(IDD_SETTING_DLG,GetDlgItem(IDC_SETTING_WIN));
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

	GetClientRect(m_newRect);
	GetClientRect(m_oldRect);


	// 加载文件
	std::ifstream readStream("d:\\room.json");
	if (readStream.is_open())
	{
		std::string result;
		readStream >> result;

		Json::Value output;
		Json::Reader reader;
		reader.parse(result,output);

		HGLOG_DEBUG(output.toStyledString());
		HG_SceneCenter::inst().load(output);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRenderOperatorDlg::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
	GetClientRect(m_newRect);
	CRect offset = CRect(
		m_newRect.left - m_oldRect.left,
		m_newRect.top - m_oldRect.top,
		m_newRect.right - m_oldRect.right,
		m_newRect.bottom - m_oldRect.bottom
		);
	m_oldRect = m_newRect;


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
	//HACK: 下面两行设置的时候会有VS异常，执行不会中断，但要注意
	//HACK- RenderOperator.exe 中的 0x78b945e5 处最可能的异常: 0xC0000005: 读取位置 0x0000006c 时发生访问冲突
	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_paramSettingDlgContainerRect.Width());	
	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_paramSettingDlgContainerRect.Width());	

	Invalidate(TRUE);
}

void CRenderOperatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRenderOperatorDlg::OnPaint()
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
HCURSOR CRenderOperatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




