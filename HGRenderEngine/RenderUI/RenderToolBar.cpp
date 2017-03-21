// RenderToolBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RenderToolBar.h"
#include "afxdialogex.h"


// RenderToolBar �Ի���

IMPLEMENT_DYNAMIC(RenderToolBar, CDialogEx)

RenderToolBar::RenderToolBar(CWnd* pParent /*=NULL*/)
	: DialogPlus(RenderToolBar::IDD, pParent)
{

}

RenderToolBar::~RenderToolBar()
{
}

void RenderToolBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(RenderToolBar, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE_BTN, &RenderToolBar::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_ZOOM_ORIGIN_BTN, &RenderToolBar::OnBnClickedZoomOriginBtn)
	ON_BN_CLICKED(IDC_ZOOM_FIT_BTN, &RenderToolBar::OnBnClickedZoomFitBtn)
END_MESSAGE_MAP()


// RenderToolBar ��Ϣ�������


BOOL RenderToolBar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBtnImage(IDC_SAVE_BTN,IDB_SAVE_BMP);
	SetBtnImage(IDC_ZOOM_ORIGIN_BTN,IDB_ZOOM_ORIGIN_BMP);
	SetBtnImage(IDC_ZOOM_FIT_BTN,IDB_ZOOM_FIT_BMP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void RenderToolBar::OnBnClickedSaveBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::CMD::RENDER_SAVE_IMAGE,NULL,NULL);
}


void RenderToolBar::OnBnClickedZoomOriginBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::CMD::RENDER_ZOOM_ORIGIN_IMAGE,NULL,NULL);
}


void RenderToolBar::OnBnClickedZoomFitBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::CMD::RENDER_ZOOM_FIT_IMAGE,NULL,NULL);
}
