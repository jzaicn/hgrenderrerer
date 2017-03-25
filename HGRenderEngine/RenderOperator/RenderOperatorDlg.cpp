
// RenderOperatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RenderOperator.h"
#include "RenderOperatorDlg.h"
#include "afxdialogex.h"
#include "JsonCpp/json.h"
#include <fstream>
#include "HgLog/HgLog.h"
// #include "HG_SceneCenter.h"
// #include "RenderManager.h"

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
END_MESSAGE_MAP()

#endif

UINT CRenderOperatorDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

//////////////////////////////////////////////////////////////////////////
// CRenderOperatorDlg ��Ϣ�������
#if 1
BOOL CRenderOperatorDlg::OnInitDialog()
{
	DialogPlus::OnInitDialog();
	//TODO: �Ժ����������ļ��������������init logger
	HgLog::HgLog::initDebugLogCategory();
	
	ShareHwnd(GetSafeHwnd());

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
	m_wndStatusBar.SetPaneInfo(0,indicators[0],SBPS_NORMAL, statusRect.Width() - m_paramSettingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneInfo(1,indicators[1],SBPS_NORMAL, m_paramSettingDlgContainerRect.Width());
	m_wndStatusBar.SetPaneText(0,HGCode::convert("׼������"));
	m_wndStatusBar.SetPaneText(1,HGCode::convert("��ǰ���űȣ�100%"));
	
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
	
	ShowWindow(SW_MAXIMIZE);

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
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_SAVE_IMAGE,NULL,NULL);
}
//"�˳�"
afx_msg void CRenderOperatorDlg::menu_exit()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_EXIT,NULL,NULL);
}
//"���ŵ�ԭʼ�ߴ�"
afx_msg void CRenderOperatorDlg::menu_zoom_origin()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_ZOOM_ORIGIN_IMAGE,NULL,NULL);
}
//"���ŵ���Ӧ����"
afx_msg void CRenderOperatorDlg::menu_zoom_fit()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_ZOOM_FIT_IMAGE,NULL,NULL);
}
//"������"
afx_msg void CRenderOperatorDlg::menu_toolbar()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_TOOLBAR_SHOW_HIDE,NULL,NULL);
}
//"ͼƬ�������"
afx_msg void CRenderOperatorDlg::menu_param_panel()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_PARAM_SHOW_HIDE,NULL,NULL);
}
//"��ȾЧ�����"
afx_msg void CRenderOperatorDlg::menu_settings_panel()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_SETTINGS_SHOW_HIDE,NULL,NULL);
}
//"״̬��"
afx_msg void CRenderOperatorDlg::menu_status()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_STATUS_SHOW_HIDE,NULL,NULL);
}
//"�ָ�Ĭ�ϲ���"
afx_msg void CRenderOperatorDlg::menu_default_display()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_DEFAULT_LAYOUT,NULL,NULL);
}
//"������Ϣ"
afx_msg void CRenderOperatorDlg::menu_help()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_HELP,NULL,NULL);
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

// 	HG_SceneCenter::inst().set_exposure(paramSettingDlg.get_Exposure());
// 	HG_SceneCenter::inst().set_sky(paramSettingDlg.get_SkyLight());
// 	HG_SceneCenter::inst().set_sun(paramSettingDlg.get_SunLight());
// 	HG_SceneCenter::inst().set_param(imageSettingDlg.get_RenderParam());
// 
// 	//RenderManager::inst().SaveESS("D:\\my_scene.ess");
// 	
// 	RenderManager::inst().Begin();

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

#endif

#include "HGCode.h"
void CRenderOperatorDlg::OnBnClickedButton1()
{
	CString cstr = HGCode::convert("������");

	const char* p = nullptr;
	p = HGCode::convert(cstr);
	HGLOG_DEBUG(p);

	std::string sstr = "��ϯ����ʦ";
	CString cstr2 = HGCode::convert(sstr);
	MessageBox(cstr2);


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
