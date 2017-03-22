
// RenderOperatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RenderOperator.h"
#include "RenderOperatorDlg.h"
#include "afxdialogex.h"

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
	: CDialogEx(CRenderOperatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenderOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRenderOperatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRenderOperatorDlg 消息处理程序

BOOL CRenderOperatorDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

#include "XmlHandlePlus.h"
#include "HgLog/HgLog.h"
#include "JsonCpp/json.h"
#include "Elara/ElaraHomeAPI.h"
#include "Elara/esslib.h"
void CRenderOperatorDlg::OnBnClickedButton1()
{
 	HgLog::HgLog::initDebugLogCategory();
	Json::Value root;
	Json::Reader reader;
	reader.parse("{\"hello\":\"宏光\"}",root);
	HGLOG_DEBUG(root.toStyledString());

	EH_Context* context =  EH_create();
	
	EH_Sky sky;
	sky.enabled= true;
	sky.hdri_name = "asdadad";
	sky.hdri_rotation = 0.0;
	sky.intensity = 50.0;

	EssExporter* ess = reinterpret_cast<EssExporter*>(context);

	EH_set_sky(context,&sky);
	EH_delete(context);

// 	TiXmlDocument doc;
// 	doc.LoadFile("E:\\HGRENDER\\trunk\\HGRenderEngine\\RenderOperator\\ImageParam.xml");
//  	XmlHandlePlus docHandler(&doc);
//  
//  	std::vector<TiXmlNode*> nodes = docHandler.findAll("/Root/Param/");
//  	for (auto it = nodes.begin(); it != nodes.end() ; it++)
//  	{
// 		HGLOG_DEBUG("0");
// 		XmlHandlePlus node(*it);
// 		if (node.getAttr("en_name").compare("RenderQuality") == 0)
// 		{
// 			std::vector<TiXmlNode*> options = node.findAll("Option");
// 			for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
// 			{
// 				XmlHandlePlus optItemPlus(*optItem);
// 				m_RenderQuality.AddString(optItemPlus.getAttr("cn_name").c_str());
// 			}
// 			m_RenderQuality.SetCurSel(atoi(node.getAttr("default").c_str()));
// 		}
// 		else if (node.getAttr("en_name").compare("ImageSize") == 0)
// 		{
// 			std::vector<TiXmlNode*> options = node.findAll("Option");
// 			for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
// 			{
// 				XmlHandlePlus optItemPlus(*optItem);
// 				m_ImageSize.AddString(optItemPlus.getAttr("cn_name").c_str());
// 			}
// 			m_ImageSize.SetCurSel(atoi(node.getAttr("default").c_str()));
// 		}
//	}
}


void CRenderOperatorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
 	GetClientRect(m_newRect);
 	CRect offset = CRect(
 		m_newRect.left - m_oldRect.left,
 		m_newRect.top - m_oldRect.top,
 		m_newRect.right - m_oldRect.right,
 		m_newRect.bottom - m_oldRect.bottom
 		);
 	m_oldRect = m_newRect;
 	
 	//移动状态栏
 	CRect statusRect;
 	GetClientRect(statusRect);
 	m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);
// 	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_paramSettingDlgContainerRect.Width());
// 	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_paramSettingDlgContainerRect.Width());
// 
 	Invalidate(TRUE);
}
