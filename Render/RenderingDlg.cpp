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


BOOL RenderingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	afxAmbientActCtx = FALSE;

	// 绑定设置子窗口
	settingDlg.Create(IDD_SETTINGDLG,GetDlgItem(IDC_SETTING_WIN));
	settingDlg.ShowWindow(SW_SHOW);
	settingDlg.GetWindowRect(m_settingDlgRect);
	
	GetDlgItem(IDC_SETTING_WIN)->GetWindowRect(m_settingDlgContainerRect);


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
	
	m_settingDlgContainerRect.left += offset.right;
	m_settingDlgContainerRect.right += offset.right;
	m_settingDlgContainerRect.top += offset.top;
	m_settingDlgContainerRect.bottom += offset.bottom;

	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_settingDlgContainerRect);
}
