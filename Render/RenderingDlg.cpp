// RenderingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Render.h"
#include "RenderingDlg.h"
#include "afxdialogex.h"


// RenderingDlg �Ի���

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


// RenderingDlg ��Ϣ�������
UINT RenderingDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

BOOL RenderingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	afxAmbientActCtx = FALSE;

	// �������Ӵ���
	settingDlg.Create(IDD_SETTINGDLG,GetDlgItem(IDC_SETTING_WIN));
	settingDlg.ShowWindow(SW_SHOW);
	settingDlg.GetWindowRect(m_settingDlgRect);
	
	GetDlgItem(IDC_SETTING_WIN)->GetWindowRect(m_settingDlgContainerRect);
	ScreenToClient(m_settingDlgContainerRect);
	m_settingDlgContainerRect.top +=1;
	m_settingDlgContainerRect.bottom +=1;
	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_settingDlgContainerRect);

	//����״̬��
	CRect rect;
    GetClientRect(rect);
    if(!m_wndStatusBar.Create(this)|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))) return false;
    m_wndStatusBar.MoveWindow(0,rect.bottom-20,rect.right,20);// ����״̬����λ�úʹ�С

	//����������
    if (!m_wndToolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)) return FALSE;
    m_wndToolbar.LoadToolBar(IDR_RENDER_TOOLBAR);  //IDR_TOOLBAR1���ǲ���һ�����ӵ�toolbar resource
    m_wndToolbar.ShowWindow(SW_SHOW);  //�����Դ���ȥ������Ҳ����
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE; 
}


void RenderingDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//�ƶ����Դ���
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

	//�ƶ�״̬��
	CRect statusRect;
    GetClientRect(statusRect);
	m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);
}
