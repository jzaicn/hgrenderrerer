// DialogRenderToolBar.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogRenderToolBar.h"
#include "afxdialogex.h"
#include "HgLog/HgLog.h"

// DialogRenderToolBar 对话框

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


// DialogRenderToolBar 消息处理程序


BOOL DialogRenderToolBar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBtnImage(IDC_SAVE_BTN,IDB_SAVE_BMP);
	SetBtnImage(IDC_ZOOM_ORIGIN_BTN,IDB_ZOOM_ORIGIN_BMP);
	SetBtnImage(IDC_ZOOM_FIT_BTN,IDB_ZOOM_FIT_BMP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DialogRenderToolBar::OnBnClickedSaveBtn()
{
	Post(RENDER_SAVE_IMAGE);
}


void DialogRenderToolBar::OnBnClickedZoomOriginBtn()
{
	Post(RENDER_ZOOM_ORIGIN_IMAGE);
}


void DialogRenderToolBar::OnBnClickedZoomFitBtn()
{
	Post(RENDER_ZOOM_FIT_IMAGE);
}
