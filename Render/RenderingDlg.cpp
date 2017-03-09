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
END_MESSAGE_MAP()


// RenderingDlg 消息处理程序
UINT RenderingDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

BOOL RenderingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	afxAmbientActCtx = FALSE;

	// 绑定设置子窗口
	settingDlg.Create(IDD_SETTINGDLG,GetDlgItem(IDC_SETTING_WIN));
	settingDlg.ShowWindow(SW_SHOW);
	settingDlg.GetWindowRect(m_settingDlgRect);
	
	GetDlgItem(IDC_SETTING_WIN)->GetWindowRect(m_settingDlgContainerRect);
	ScreenToClient(m_settingDlgContainerRect);
	m_settingDlgContainerRect.top +=1;
	m_settingDlgContainerRect.bottom +=1;
	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_settingDlgContainerRect);

	//创建状态栏
	CRect rect;
    GetClientRect(rect);
    if(!m_wndStatusBar.Create(this)|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))) return false;
    m_wndStatusBar.MoveWindow(0,rect.bottom-20,rect.right,20);// 调整状态栏的位置和大小

	//创建工具条
    if (!m_wndToolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)) return FALSE;
    m_wndToolbar.LoadToolBar(IDR_RENDER_TOOLBAR);  //IDR_TOOLBAR1既是步骤一中增加的toolbar resource
    m_wndToolbar.ShowWindow(SW_SHOW);  //经测试此行去掉好像也可以
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE; 
}


void RenderingDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//移动属性窗口
	CRect winrect;
	GetWindowRect(winrect);
	CDialog::OnSizing(fwSide, pRect);
	CRect rect(pRect->left,pRect->top,pRect->left,pRect->bottom);
	
	CRect offset(0,0,0,0);
	offset.left = pRect->left - winrect.left;
	offset.right = pRect->right - winrect.right;
	offset.top = pRect->top - winrect.top;
	offset.bottom = pRect->bottom - winrect.bottom;
	
	m_settingDlgContainerRect.left += offset.right;
	m_settingDlgContainerRect.right += offset.right;
	m_settingDlgContainerRect.top += offset.top;
	m_settingDlgContainerRect.bottom += offset.bottom;

	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_settingDlgContainerRect);

	//移动状态栏
	CRect statusRect;
    GetClientRect(statusRect);
	m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);
}
