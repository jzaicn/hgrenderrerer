// RenderingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Render.h"
#include "RenderingDlg.h"
#include "afxdialogex.h"
#include "RenderManager.h"


#pragma comment(lib,"HgLog.lib")
#pragma comment(lib,"log4cpp.lib")

// RenderingDlg �Ի���

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
	
	ON_MESSAGE(RENDER_SAVE_IMAGE,&RenderingDlg::OnSaveImage)	// ��ͼ��
	ON_MESSAGE(RENDER_LOAD_IMAGE,&RenderingDlg::OnLoadImage)	// ����ͼ��
	ON_MESSAGE(RENDER_EXIT,&RenderingDlg::OnExit)	// �˳�
	ON_MESSAGE(RENDER_ZOOM_ORIGIN_IMAGE,&RenderingDlg::OnZoomOriginImage)	// ����ͼ��ԭʼ�ߴ�
	ON_MESSAGE(RENDER_ZOOM_FIT_IMAGE,&RenderingDlg::OnZoomFitImage)	// ����ͼ����Ӧ����
	ON_MESSAGE(RENDER_ZOOM_IN_IMAGE,&RenderingDlg::OnZoomInImage)	// �Ŵ�ͼ��
	ON_MESSAGE(RENDER_ZOOM_OUT_IMAGE,&RenderingDlg::OnZoomOutImage)	// ��Сͼ��
	ON_MESSAGE(RENDER_TOOLBAR_SHOW_HIDE,&RenderingDlg::OnToolbarShowHide)	// ������ ����/��ʾ
	ON_MESSAGE(RENDER_DISPLAY_SHOW_HIDE,&RenderingDlg::OnDisplayShowHide)	// ��ȾЧ������  ����/��ʾ
	ON_MESSAGE(RENDER_STATUS_SHOW_HIDE,&RenderingDlg::OnStatusShowHide)	// ״̬��  ����/��ʾ
	ON_MESSAGE(RENDER_DEFAULT_LAYOUT,&RenderingDlg::OnDefaultLayout)	// �ָ�Ĭ�ϲ��� 
	ON_MESSAGE(RENDER_SAVE_LAYOUT,&RenderingDlg::OnSaveLayout)	// ���沼�� 
	ON_MESSAGE(RENDER_LOAD_LAYOUT,&RenderingDlg::OnLoadLayout)	// �ָ����� 
	ON_MESSAGE(RENDER_HELP,&RenderingDlg::OnHelp)	// ����
	ON_MESSAGE(RENDER_SAVE_SETTINGS,&RenderingDlg::OnSaveSettings)	// ��������
	ON_MESSAGE(RENDER_LOAD_SETTINGS,&RenderingDlg::OnLoadSettings)	// ��ȡ����
	ON_MESSAGE(RENDER_BEGIN,&RenderingDlg::OnBegin)	// ��Ⱦ��ʼ
	ON_MESSAGE(RENDER_STOP,&RenderingDlg::OnStop)	// ��Ⱦֹͣ
	ON_MESSAGE(RENDER_DONE,&RenderingDlg::OnDone)	// ��Ⱦֹͣ
END_MESSAGE_MAP()


// RenderingDlg ��Ϣ�������
UINT RenderingDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

BOOL RenderingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	HgLog::HgLog::initDebugLogCategory();
	ShareHwnd(m_hWnd);
	afxAmbientActCtx = FALSE;

	// ��ͼ�Ի���
	displayResultDlg.Create(IDD_DISPLAY_DLG,GetDlgItem(IDC_DISPLAYRESULT_WIN));
	displayResultDlg.ShowWindow(SW_SHOW);
	displayResultDlg.GetWindowRect(m_toolBarDlgRect);
	GetDlgItem(IDC_DISPLAYRESULT_WIN)->GetWindowRect(m_displayResultDlgContainerRect);
	ScreenToClient(m_displayResultDlgContainerRect);

	// �������Ի���
	toolBarDlg.Create(IDD_TOOLBAR_DLG,GetDlgItem(IDC_TOOLBAR_WIN));
	toolBarDlg.ShowWindow(SW_SHOW);
	toolBarDlg.GetWindowRect(m_toolBarDlgRect);
	GetDlgItem(IDC_TOOLBAR_WIN)->GetWindowRect(m_toolBarDlgContainerRect);
	ScreenToClient(m_toolBarDlgContainerRect);

	// ͼƬ�Ի���
	imageSettingDlg.Create(IDD_IMAGE_DLG,GetDlgItem(IDC_IMAGE_WIN));
	imageSettingDlg.ShowWindow(SW_SHOW);
	imageSettingDlg.GetWindowRect(m_imageSettingDlgRect);
	GetDlgItem(IDC_IMAGE_WIN)->GetWindowRect(m_imageSettingDlgContainerRect);
	ScreenToClient(m_imageSettingDlgContainerRect);

	// ���ò����Ի���
	paramSettingDlg.Create(IDD_SETTINGDLG,GetDlgItem(IDC_SETTING_WIN));
	paramSettingDlg.ShowWindow(SW_SHOW);
	paramSettingDlg.GetWindowRect(m_paramSettingDlgRect);
	GetDlgItem(IDC_SETTING_WIN)->GetWindowRect(m_paramSettingDlgContainerRect);
	ScreenToClient(m_paramSettingDlgContainerRect);


	//����״̬��
	CRect statusRect;
    GetClientRect(statusRect);
    if(!m_wndStatusBar.Create(this)|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))) return false;
    m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);// ����״̬����λ�úʹ�С
	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_paramSettingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_paramSettingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneText(0,"׼������");
	m_wndStatusBar.SetPaneText(1,"��ǰ���űȣ�100%");

	return TRUE; 
}


void RenderingDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CRect offset = getOffset(fwSide,pRect);
	CDialog::OnSizing(fwSide, pRect);
	
	//�ƶ�ͼƬ����
	m_displayResultDlgContainerRect.left += offset.left;
	m_displayResultDlgContainerRect.right += offset.right;
	m_displayResultDlgContainerRect.top += offset.top;
	m_displayResultDlgContainerRect.bottom += offset.bottom;
	GetDlgItem(IDC_DISPLAYRESULT_WIN)->MoveWindow(m_displayResultDlgContainerRect);
	displayResultDlg.MoveWindow(0,0,m_displayResultDlgContainerRect.Width(),m_displayResultDlgContainerRect.Height());

	//����������
	m_toolBarDlgContainerRect.left += offset.left;
	m_toolBarDlgContainerRect.right += offset.right;
	m_toolBarDlgContainerRect.top += offset.top;
	m_toolBarDlgContainerRect.bottom += offset.top;
	GetDlgItem(IDC_TOOLBAR_WIN)->MoveWindow(m_toolBarDlgContainerRect);

	//�ƶ�ͼƬ����
	m_imageSettingDlgContainerRect.left += offset.right;
	m_imageSettingDlgContainerRect.right += offset.right;
	m_imageSettingDlgContainerRect.top += offset.top;
	m_imageSettingDlgContainerRect.bottom += offset.top;
	GetDlgItem(IDC_IMAGE_WIN)->MoveWindow(m_imageSettingDlgContainerRect);

	//�ƶ����Դ���
	m_paramSettingDlgContainerRect.left += offset.right;
	m_paramSettingDlgContainerRect.right += offset.right;
	m_paramSettingDlgContainerRect.top += offset.top;
	m_paramSettingDlgContainerRect.bottom += offset.bottom;
	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_paramSettingDlgContainerRect);


	//�ƶ�״̬��
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

