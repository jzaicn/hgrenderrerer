
// RenderOperatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RenderOperator.h"
#include "RenderOperatorDlg.h"
#include "afxdialogex.h"
#include "JsonCpp/json.h"
#include <fstream>
#include "HgLog/HgLog.h"
#include "HG_SceneCenter.h"
#include "RenderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
#if 1

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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
// CRenderOperatorDlg �Ի���
#if 1



CRenderOperatorDlg::CRenderOperatorDlg(CWnd* pParent /*=NULL*/)
	: DialogPlus(CRenderOperatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenderOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	DialogPlus::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RENDER_PROGRESS, m_render_process);
}

BEGIN_MESSAGE_MAP(CRenderOperatorDlg, DialogPlus)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CRenderOperatorDlg::OnBnClickedButton1)

	//////////////////////////////////////////////////////////////////////////
	// �˵�����
	//"�ļ�"
	ON_COMMAND(MENU_SAVE_IMAGE,&CRenderOperatorDlg::menu_save_image)			//"����ͼ��"
	ON_COMMAND(MENU_EXIT,&CRenderOperatorDlg::menu_exit)						//"�˳�"
	//"�༭"
	ON_COMMAND(MENU_ZOOM_ORIGIN,&CRenderOperatorDlg::menu_zoom_origin)				//"���ŵ�ԭʼ�ߴ�"
	ON_COMMAND(MENU_ZOOM_FIT,&CRenderOperatorDlg::menu_zoom_fit)				//"���ŵ���Ӧ����"
	//"����"
	ON_COMMAND(MENU_TOOLBAR,&CRenderOperatorDlg::menu_toolbar)					//"������"
	ON_COMMAND(MENU_PARAM_PANEL,&CRenderOperatorDlg::menu_param_panel)		//"��ȾЧ�����"
	ON_COMMAND(MENU_SETTING_PANEL,&CRenderOperatorDlg::menu_settings_panel)		//"��ȾЧ�����"
	ON_COMMAND(MENU_STATUS,&CRenderOperatorDlg::menu_status)					//"״̬��"
	ON_COMMAND(MENU_DEFAULT_DISPLAY,&CRenderOperatorDlg::menu_default_display)	//"�ָ�Ĭ�ϲ���"
	//"����"
	ON_COMMAND(MENU_HELP,&CRenderOperatorDlg::menu_help)						//"������Ϣ"

	//////////////////////////////////////////////////////////////////////////
	// �Զ�����Ϣ
	ON_MESSAGE(RENDER_SAVE_IMAGE,&CRenderOperatorDlg::OnSaveImage)	// ��ͼ��
	ON_MESSAGE(RENDER_LOAD_IMAGE,&CRenderOperatorDlg::OnLoadImage)	// ����ͼ��
	ON_MESSAGE(RENDER_EXIT,&CRenderOperatorDlg::OnExit)	// �˳�
	ON_MESSAGE(RENDER_ZOOM_ORIGIN_IMAGE,&CRenderOperatorDlg::OnZoomOriginImage)	// ����ͼ��ԭʼ�ߴ�
	ON_MESSAGE(RENDER_ZOOM_FIT_IMAGE,&CRenderOperatorDlg::OnZoomFitImage)	// ����ͼ����Ӧ����
	ON_MESSAGE(RENDER_ZOOM_IN_IMAGE,&CRenderOperatorDlg::OnZoomInImage)	// �Ŵ�ͼ��
	ON_MESSAGE(RENDER_ZOOM_OUT_IMAGE,&CRenderOperatorDlg::OnZoomOutImage)	// ��Сͼ��
	ON_MESSAGE(RENDER_TOOLBAR_SHOW_HIDE,&CRenderOperatorDlg::OnToolbarShowHide)	// ������ ����/��ʾ
	ON_MESSAGE(RENDER_PARAM_SHOW_HIDE,&CRenderOperatorDlg::OnParamShowHide)		// ͼƬ�ߴ�����  ����/��ʾ
	ON_MESSAGE(RENDER_SETTINGS_SHOW_HIDE,&CRenderOperatorDlg::OnSettingShowHide)// ��ȾЧ������  ����/��ʾ
	ON_MESSAGE(RENDER_DISPLAY_SHOW_HIDE,&CRenderOperatorDlg::OnDisplayShowHide)	// ��ȾЧ����ʾ  ����/��ʾ
	ON_MESSAGE(RENDER_STATUS_SHOW_HIDE,&CRenderOperatorDlg::OnStatusShowHide)	// ״̬��  ����/��ʾ
	ON_MESSAGE(RENDER_DEFAULT_LAYOUT,&CRenderOperatorDlg::OnDefaultLayout)	// �ָ�Ĭ�ϲ��� 
	ON_MESSAGE(RENDER_SAVE_LAYOUT,&CRenderOperatorDlg::OnSaveLayout)	// ���沼�� 
	ON_MESSAGE(RENDER_LOAD_LAYOUT,&CRenderOperatorDlg::OnLoadLayout)	// �ָ����� 
	ON_MESSAGE(RENDER_HELP,&CRenderOperatorDlg::OnHelp)	// ����
	ON_MESSAGE(RENDER_SAVE_SETTINGS,&CRenderOperatorDlg::OnSaveSettings)	// ��������
	ON_MESSAGE(RENDER_LOAD_SETTINGS,&CRenderOperatorDlg::OnLoadSettings)	// ��ȡ����
	ON_MESSAGE(RENDER_BEGIN,&CRenderOperatorDlg::OnBegin)	// ��Ⱦ��ʼ
	ON_MESSAGE(RENDER_STOP,&CRenderOperatorDlg::OnStop)	// ��Ⱦֹͣ
	ON_MESSAGE(RENDER_DONE,&CRenderOperatorDlg::OnDone)	// ��Ⱦֹͣ
	ON_MESSAGE(RENDER_SETTING_UPDATE,&CRenderOperatorDlg::OnSettingUpdate)	// ��Ⱦ���ø���
	ON_MESSAGE(RENDER_STATUS_UPDATE,&CRenderOperatorDlg::OnRenderStatusUpdate)	// ��Ⱦ״̬����
END_MESSAGE_MAP()

#endif

UINT CRenderOperatorDlg::indicators[] = {IDS_STATESTRING1,IDS_STATESTRING2, IDS_STATESTRING2};
int CRenderOperatorDlg::indiceWidth[] = {0,0,0};

//////////////////////////////////////////////////////////////////////////
// CRenderOperatorDlg ��Ϣ�������
#if 1
BOOL CRenderOperatorDlg::OnInitDialog()
{
	DialogPlus::OnInitDialog();
	//TODO: �Ժ����������ļ��������������init logger
	HgLog::HgLog::initDebugLogCategory();
	
	registerShareHwnd(GetSafeHwnd());

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	// ��ͼ�Ի���
	//HACK: �����Ӵ����׳��쳣
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
 	paramSettingDlg.Create(IDD_SETTING_DLG,GetDlgItem(IDC_SETTING_WIN));
 	paramSettingDlg.ShowWindow(SW_SHOW);
 	paramSettingDlg.GetWindowRect(m_paramSettingDlgRect);
	GetDlgItem(IDC_SETTING_WIN)->GetWindowRect(m_paramSettingDlgContainerRect);
	ScreenToClient(m_paramSettingDlgContainerRect);

	//����״̬��
	CRect statusRect;
	GetClientRect(statusRect);
	if(!m_wndStatusBar.Create(this)|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))) return false;
	m_wndStatusBar.MoveWindow(0,statusRect.bottom-20,statusRect.right,20);// ����״̬����λ�úʹ�С

	//״̬��Ϣ
	indiceWidth[statusbar::info] = statusRect.Width() - m_paramSettingDlgContainerRect.Width() - m_paramSettingDlgContainerRect.Width();//init��
	//indiceWidth[statusbar::info] = statusRect.Width() - indiceWidth[statusbar::process] - indiceWidth[statusbar::scale];	//onsize��
	m_wndStatusBar.SetPaneInfo(statusbar::info,indicators[statusbar::info],SBPS_NORMAL, indiceWidth[statusbar::info]);
	m_wndStatusBar.SetPaneText(statusbar::info,HGCode::convert("׼������"));//init ��

	//TODO: �Ժ���Գ���һ��SBPS_NORMAL��ΪSBPS_OWNERDRAW��������ʱ�ÿؼ�����
	//��Ⱦ����
	indiceWidth[statusbar::process] = m_paramSettingDlgContainerRect.Width();//init �򿪣��̶�
	m_wndStatusBar.SetPaneInfo(statusbar::process,indicators[statusbar::process],SBPS_NORMAL, indiceWidth[statusbar::process]);
	m_wndStatusBar.SetPaneText(statusbar::process,HGCode::convert("999999"));//init ��

	//ͼƬ���ű���
	indiceWidth[statusbar::scale] = m_paramSettingDlgContainerRect.Width();//init �򿪣��̶�
	m_wndStatusBar.SetPaneInfo(statusbar::scale,indicators[statusbar::scale],SBPS_NORMAL, indiceWidth[statusbar::scale]);
	m_wndStatusBar.SetPaneText(statusbar::scale,HGCode::convert("����100%"));//init ��

	//��Ⱦ����
	m_render_process_rect = statusRect;
	m_render_process_rect.top = statusRect.bottom - 19;
	m_render_process_rect.left = indiceWidth[statusbar::info];
	m_render_process_rect.right = m_render_process_rect.left + indiceWidth[statusbar::process];
	m_render_process.MoveWindow(m_render_process_rect);

	m_render_process.SetRange(0,100);
	m_render_process.SetStep(1);
	m_render_process.SetPos(0);

	GetClientRect(m_newRect);
	GetClientRect(m_oldRect);


// 	// �����ļ�
// 	std::ifstream readStream("d:\\room.json");
// 	if (readStream.is_open())
// 	{
// 		std::string result;
// 		readStream >> result;
// 
// 		Json::Value output;
// 		Json::Reader reader;
// 		reader.parse(result,output);
// 
// 		HGLOG_DEBUG(output.toStyledString());
// 		HG_SceneCenter::inst().load(output);
// 	}
	
	//ShowWindow(SW_MAXIMIZE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	//HACK: �����������õ�ʱ�����VS�쳣��ִ�в����жϣ���Ҫע��
	//HACK- RenderOperator.exe �е� 0x78b945e5 ������ܵ��쳣: 0xC0000005: ��ȡλ�� 0x0000006c ʱ�������ʳ�ͻ
	// 	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, indiceWidth[0]);	
	// 	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, indiceWidth[1]);	

	//״̬��Ϣ
	//indiceWidth[statusbar::info] = statusRect.Width() - m_paramSettingDlgContainerRect.Width() - m_paramSettingDlgContainerRect.Width();//init��
	indiceWidth[statusbar::info] = statusRect.Width() - indiceWidth[statusbar::process] - indiceWidth[statusbar::scale];	//onsize��
	m_wndStatusBar.SetPaneInfo(statusbar::info,indicators[statusbar::info],SBPS_NORMAL, indiceWidth[statusbar::info]);
	//m_wndStatusBar.SetPaneText(statusbar::info,HGCode::convert("׼������"));//init ��

	//TODO: �Ժ���Գ���һ��SBPS_NORMAL��ΪSBPS_OWNERDRAW��������ʱ�ÿؼ�����
	//��Ⱦ����
	//indiceWidth[statusbar::process] = m_paramSettingDlgContainerRect.Width();//init �򿪣��̶�
	m_wndStatusBar.SetPaneInfo(statusbar::process,indicators[statusbar::process],SBPS_NORMAL, indiceWidth[statusbar::process]);
	//m_wndStatusBar.SetPaneText(statusbar::process,HGCode::convert("999999"));//init ��

	//ͼƬ���ű���
	//indiceWidth[statusbar::scale] = m_paramSettingDlgContainerRect.Width();//init �򿪣��̶�
	m_wndStatusBar.SetPaneInfo(statusbar::scale,indicators[statusbar::scale],SBPS_NORMAL, indiceWidth[statusbar::scale]);
	//m_wndStatusBar.SetPaneText(statusbar::scale,HGCode::convert("����100%"));//init ��

	//HACK: ����statusbar���Ȳ�׼
	//��Ⱦ����
	m_render_process_rect = statusRect;
	m_render_process_rect.top = statusRect.bottom - 19;
	m_render_process_rect.left = indiceWidth[statusbar::info];
	m_render_process_rect.right = m_render_process_rect.left + indiceWidth[statusbar::process];
	m_render_process.MoveWindow(m_render_process_rect);

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
		DialogPlus::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRenderOperatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DialogPlus::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRenderOperatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#endif

//////////////////////////////////////////////////////////////////////////
// �˵���Ϣ
#if 1
//"����ͼ��"
afx_msg void CRenderOperatorDlg::menu_save_image()
{
	Post(RENDER_SAVE_IMAGE);
}
//"�˳�"
afx_msg void CRenderOperatorDlg::menu_exit()
{
	Post(RENDER_EXIT);
}
//"���ŵ�ԭʼ�ߴ�"
afx_msg void CRenderOperatorDlg::menu_zoom_origin()
{
	Post(RENDER_ZOOM_ORIGIN_IMAGE);
}
//"���ŵ���Ӧ����"
afx_msg void CRenderOperatorDlg::menu_zoom_fit()
{
	Post(RENDER_ZOOM_FIT_IMAGE);
}
//"������"
afx_msg void CRenderOperatorDlg::menu_toolbar()
{
	Post(RENDER_TOOLBAR_SHOW_HIDE);
}
//"ͼƬ�������"
afx_msg void CRenderOperatorDlg::menu_param_panel()
{
	Post(RENDER_PARAM_SHOW_HIDE);
}
//"��ȾЧ�����"
afx_msg void CRenderOperatorDlg::menu_settings_panel()
{
	Post(RENDER_SETTINGS_SHOW_HIDE);
}
//"״̬��"
afx_msg void CRenderOperatorDlg::menu_status()
{
	Post(RENDER_STATUS_SHOW_HIDE);
}
//"�ָ�Ĭ�ϲ���"
afx_msg void CRenderOperatorDlg::menu_default_display()
{
	Post(RENDER_DEFAULT_LAYOUT);
}
//"������Ϣ"
afx_msg void CRenderOperatorDlg::menu_help()
{
	Post(RENDER_HELP);
}
#endif

//////////////////////////////////////////////////////////////////////////
// �Զ�����Ϣ�¼�·��
#if 1
LRESULT CRenderOperatorDlg::OnSaveImage(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnSaveImage");
	return 0;
}

LRESULT CRenderOperatorDlg::OnLoadImage(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnLoadImage");
	return 0;
}

LRESULT CRenderOperatorDlg::OnExit(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnExit");
	return 0;
}

LRESULT CRenderOperatorDlg::OnZoomOriginImage(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnZoomOriginImage");
	return 0;
}

LRESULT CRenderOperatorDlg::OnZoomFitImage(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnZoomFitImage");
	return 0;
}

LRESULT CRenderOperatorDlg::OnZoomInImage(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnZoomInImage");
	return 0;
}

LRESULT CRenderOperatorDlg::OnZoomOutImage(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnZoomOutImage");
	return 0;
}

LRESULT CRenderOperatorDlg::OnToolbarShowHide(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnToolbarShowHide");
	return 0;
}

LRESULT CRenderOperatorDlg::OnParamShowHide(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnParamShowHide");
	return 0;
}

LRESULT CRenderOperatorDlg::OnSettingShowHide(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnSettingShowHide");
	return 0;
}

LRESULT CRenderOperatorDlg::OnDisplayShowHide(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnDisplayShowHide");
	return 0;
}

LRESULT CRenderOperatorDlg::OnStatusShowHide(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnStatusShowHide");
	return 0;
}

LRESULT CRenderOperatorDlg::OnDefaultLayout(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnDefaultLayout");
	return 0;
}

LRESULT CRenderOperatorDlg::OnSaveLayout(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnSaveLayout");
	return 0;
}

LRESULT CRenderOperatorDlg::OnLoadLayout(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnLoadLayout");
	return 0;
}

LRESULT CRenderOperatorDlg::OnHelp(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnHelp");
	return 0;
}

LRESULT CRenderOperatorDlg::OnSaveSettings(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnSaveSettings");
	return 0;
}

LRESULT CRenderOperatorDlg::OnLoadSettings(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnLoadSettings");
	return 0;
}

LRESULT CRenderOperatorDlg::OnBegin(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnBegin");

	HG_SceneCenter::inst().set_exposure(paramSettingDlg.get_Exposure());
	HG_SceneCenter::inst().set_sky(paramSettingDlg.get_SkyLight());
	HG_SceneCenter::inst().set_sun(paramSettingDlg.get_SunLight());
	HG_SceneCenter::inst().set_param(imageSettingDlg.get_RenderParam());

	//RenderManager::inst().SaveESS("D:\\my_scene.ess");
	
	RenderManager::inst().Begin();

	return 0;
}

LRESULT CRenderOperatorDlg::OnStop(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnStop");
	return 0;
}

LRESULT CRenderOperatorDlg::OnDone(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnDone");
	return 0;
}

LRESULT CRenderOperatorDlg::OnSettingUpdate(WPARAM w,LPARAM l)
{
	HGLOG_DEBUG("OnSettingUpdate");
	return 0;
}

LRESULT CRenderOperatorDlg::OnRenderStatusUpdate(WPARAM w,LPARAM l)
{
	RenderStatus whichStatus = (RenderStatus)w;//����

	switch (whichStatus)
	{
	case DialogPlus::update_image_scale:
		break;
	case DialogPlus::update_process:
		{
			int curpos = (int)l;
			m_render_process.SetPos(curpos);
		}
		break;
	case DialogPlus::update_status_text:
		{
			CString str = (TCHAR*)l;
			m_wndStatusBar.SetPaneText(statusbar::info,str);
		}
		break;
	default:
		break;
	}
	return 0;
}


#endif
using namespace Gdiplus;
#include "HGCode.h"
void CRenderOperatorDlg::OnBnClickedButton1()
{
// 	CString cstr = HGCode::convert("������");
// 
// 	const char* p = nullptr;
// 	p = HGCode::convert(cstr);
// 	HGLOG_DEBUG(p);
// 
// 	std::string sstr = "��ϯ����ʦ";
// 	CString cstr2 = HGCode::convert(sstr);
// 	MessageBox(cstr2);

	CRect rcDrawArea(0,0,104,1000);
	Bitmap* m_pImg = ::new Bitmap(rcDrawArea.Width(), rcDrawArea.Height());

	int index = 0;
	for (int wi = 0; wi < 104 ; wi++)
	{
		for (int hi = 0; hi < 1000 ; hi++)
		{
			// 				int r = (int)color_data[hi + index][0];				
			// 				int g = (int)color_data[hi + index][1];
			// 				int b = (int)color_data[hi + index][2];
			// 				int a = (int)color_data[hi + index][3];
			int r = rand()%255;				
			int g = rand()%255;
			int b = rand()%255;
			int a = 0xFF;

			Color color(a,b,g,r);
			m_pImg->SetPixel(wi,hi,color);
		}
		index += 1000;
	}

	DialogPlus::Send(DialogPlus::RENDER_IMAGE_UPDATE,NULL,(LPARAM)m_pImg);

// 	Json::Value root;
// 
// 	root["123"] = 123;


// 	HG_RenderParam contex=imageSettingDlg.get_RenderParam();
// 	HG_Exposure exp  = paramSettingDlg.get_Exposure();
// 	HG_SunLight sun = paramSettingDlg.get_SunLight();
// 	HG_SkyLight sky = paramSettingDlg.get_SkyLight();
// 
// 	exp.set_exposure_enable(!exp.get_exposure_enable());
// 	paramSettingDlg.set_Exposure(exp);
// 	paramSettingDlg.set_SunLight(sun);
// 	paramSettingDlg.set_SkyLight(sky);
// 	imageSettingDlg.set_RenderParam(param);
// 
// 	//TODO: �޸��ػ沿�֣�ʹ�����Ʃ��ѡ��״̬��
// 	Invalidate();
}
