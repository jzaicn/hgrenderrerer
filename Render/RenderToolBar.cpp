// RenderToolBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Render.h"
#include "RenderToolBar.h"
#include "afxdialogex.h"


// RenderToolBar �Ի���

IMPLEMENT_DYNAMIC(RenderToolBar, CDialogEx)

RenderToolBar::RenderToolBar(CWnd* pParent /*=NULL*/)
	: CDialogEx(RenderToolBar::IDD, pParent)
{

}

RenderToolBar::~RenderToolBar()
{
}

void RenderToolBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void RenderToolBar::SetBtnImage(int _btn_marco,int _res_marco)
{
	HBITMAP   hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(_res_marco)); // IDB_BITMAP_TESTΪ��ԴͼƬID 
	((CButton *)GetDlgItem(_btn_marco))->SetBitmap(hBitmap);
}

BEGIN_MESSAGE_MAP(RenderToolBar, CDialogEx)
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
