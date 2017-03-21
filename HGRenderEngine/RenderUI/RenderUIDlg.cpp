
// RenderUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RenderUI.h"
#include "RenderUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CRenderUIDlg �Ի���




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

// 	ON_MESSAGE(RENDER_SAVE_IMAGE,&CRenderUIDlg::OnSaveImage)	// ��ͼ��
// 	ON_MESSAGE(RENDER_LOAD_IMAGE,&CRenderUIDlg::OnLoadImage)	// ����ͼ��
// 	ON_MESSAGE(RENDER_EXIT,&CRenderUIDlg::OnExit)	// �˳�
// 	ON_MESSAGE(RENDER_ZOOM_ORIGIN_IMAGE,&CRenderUIDlg::OnZoomOriginImage)	// ����ͼ��ԭʼ�ߴ�
// 	ON_MESSAGE(RENDER_ZOOM_FIT_IMAGE,&CRenderUIDlg::OnZoomFitImage)	// ����ͼ����Ӧ����
// 	ON_MESSAGE(RENDER_ZOOM_IN_IMAGE,&CRenderUIDlg::OnZoomInImage)	// �Ŵ�ͼ��
// 	ON_MESSAGE(RENDER_ZOOM_OUT_IMAGE,&CRenderUIDlg::OnZoomOutImage)	// ��Сͼ��
// 	ON_MESSAGE(RENDER_TOOLBAR_SHOW_HIDE,&CRenderUIDlg::OnToolbarShowHide)	// ������ ����/��ʾ
// 	ON_MESSAGE(RENDER_DISPLAY_SHOW_HIDE,&CRenderUIDlg::OnDisplayShowHide)	// ��ȾЧ������  ����/��ʾ
// 	ON_MESSAGE(RENDER_STATUS_SHOW_HIDE,&CRenderUIDlg::OnStatusShowHide)	// ״̬��  ����/��ʾ
// 	ON_MESSAGE(RENDER_DEFAULT_LAYOUT,&CRenderUIDlg::OnDefaultLayout)	// �ָ�Ĭ�ϲ��� 
// 	ON_MESSAGE(RENDER_SAVE_LAYOUT,&CRenderUIDlg::OnSaveLayout)	// ���沼�� 
// 	ON_MESSAGE(RENDER_LOAD_LAYOUT,&CRenderUIDlg::OnLoadLayout)	// �ָ����� 
// 	ON_MESSAGE(RENDER_HELP,&CRenderUIDlg::OnHelp)	// ����
// 	ON_MESSAGE(RENDER_SAVE_SETTINGS,&CRenderUIDlg::OnSaveSettings)	// ��������
// 	ON_MESSAGE(RENDER_LOAD_SETTINGS,&CRenderUIDlg::OnLoadSettings)	// ��ȡ����
// 	ON_MESSAGE(RENDER_BEGIN,&CRenderUIDlg::OnBegin)	// ��Ⱦ��ʼ
// 	ON_MESSAGE(RENDER_STOP,&CRenderUIDlg::OnStop)	// ��Ⱦֹͣ
// 	ON_MESSAGE(RENDER_DONE,&CRenderUIDlg::OnDone)	// ��Ⱦֹͣ
ON_WM_SIZE()
END_MESSAGE_MAP()

//CRenderUIDlg ��Ϣ�������
UINT CRenderUIDlg::indicators[] = {IDS_STATESTRING1, IDS_STATESTRING2};

// CRenderUIDlg ��Ϣ�������

BOOL CRenderUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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


	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//TODO: ����д����bug���ڴ������ڣ��ڲ�move��ʱ��ᱨ��
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

	m_oldRect = statusRect;
	m_newRect = statusRect;
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// void CRenderUIDlg::OnSizing(UINT fwSide, LPRECT pRect)
// {
// 	CRect offset = getOffset(fwSide,pRect);
// 	CDialog::OnSizing(fwSide, pRect);
// 
// // 	//�ƶ�ͼƬ����
// // 	m_displayResultDlgContainerRect.left += offset.left;
// // 	m_displayResultDlgContainerRect.right += offset.right;
// // 	m_displayResultDlgContainerRect.top += offset.top;
// // 	m_displayResultDlgContainerRect.bottom += offset.bottom;
// // 	GetDlgItem(IDC_DISPLAYRESULT_WIN)->MoveWindow(m_displayResultDlgContainerRect);
// // 	displayResultDlg.MoveWindow(0,0,m_displayResultDlgContainerRect.Width(),m_displayResultDlgContainerRect.Height());
// // 
// // 	//����������
// // 	m_toolBarDlgContainerRect.left += offset.left;
// // 	m_toolBarDlgContainerRect.right += offset.right;
// // 	m_toolBarDlgContainerRect.top += offset.top;
// // 	m_toolBarDlgContainerRect.bottom += offset.top;
// // 	GetDlgItem(IDC_TOOLBAR_WIN)->MoveWindow(m_toolBarDlgContainerRect);
// // 
// // 	//�ƶ�ͼƬ����
// // 	m_imageSettingDlgContainerRect.left += offset.right;
// // 	m_imageSettingDlgContainerRect.right += offset.right;
// // 	m_imageSettingDlgContainerRect.top += offset.top;
// // 	m_imageSettingDlgContainerRect.bottom += offset.top;
// // 	GetDlgItem(IDC_IMAGE_WIN)->MoveWindow(m_imageSettingDlgContainerRect);
// // 
// // 	//�ƶ����Դ���
// // 	m_paramSettingDlgContainerRect.left += offset.right;
// // 	m_paramSettingDlgContainerRect.right += offset.right;
// // 	m_paramSettingDlgContainerRect.top += offset.top;
// // 	m_paramSettingDlgContainerRect.bottom += offset.bottom;
// // 	GetDlgItem(IDC_SETTING_WIN)->MoveWindow(m_paramSettingDlgContainerRect);
// // 
// // 
// // 	//�ƶ�״̬��
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRenderUIDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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



}
