
// RenderOperatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RenderOperator.h"
#include "RenderOperatorDlg.h"
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


// CRenderOperatorDlg �Ի���




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
	ON_BN_CLICKED(IDC_BUTTON1, &CRenderOperatorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CRenderOperatorDlg ��Ϣ�������

BOOL CRenderOperatorDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRenderOperatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "XmlHandlePlus.h"
#include "HgLog/HgLog.h"
#include "JsonCpp/json.h"

void CRenderOperatorDlg::OnBnClickedButton1()
{
 	HgLog::HgLog::initDebugLogCategory();
	Json::Value root;
	Json::Reader reader;
	reader.parse("{\"hello\":\"���\"}",root);
	HGLOG_DEBUG(root.toStyledString());


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
