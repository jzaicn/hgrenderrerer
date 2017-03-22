// DialogRenderToolBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogRenderToolBar.h"
#include "afxdialogex.h"


// DialogRenderToolBar �Ի���

IMPLEMENT_DYNAMIC(DialogRenderToolBar, CDialogEx)

DialogRenderToolBar::DialogRenderToolBar(CWnd* pParent /*=NULL*/)
	: DialogPlus(DialogRenderToolBar::IDD, pParent)
{

}

DialogRenderToolBar::~DialogRenderToolBar()
{
}

void DialogRenderToolBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(DialogRenderToolBar, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE_BTN, &DialogRenderToolBar::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_ZOOM_ORIGIN_BTN, &DialogRenderToolBar::OnBnClickedZoomOriginBtn)
	ON_BN_CLICKED(IDC_ZOOM_FIT_BTN, &DialogRenderToolBar::OnBnClickedZoomFitBtn)
END_MESSAGE_MAP()


// DialogRenderToolBar ��Ϣ��������


BOOL DialogRenderToolBar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBtnImage(IDC_SAVE_BTN,IDB_SAVE_BMP);
	SetBtnImage(IDC_ZOOM_ORIGIN_BTN,IDB_ZOOM_ORIGIN_BMP);
	SetBtnImage(IDC_ZOOM_FIT_BTN,IDB_ZOOM_FIT_BMP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void DialogRenderToolBar::OnBnClickedSaveBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_SAVE_IMAGE,NULL,NULL);
}


void DialogRenderToolBar::OnBnClickedZoomOriginBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_ZOOM_ORIGIN_IMAGE,NULL,NULL);
}


void DialogRenderToolBar::OnBnClickedZoomFitBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_ZOOM_FIT_IMAGE,NULL,NULL);
}