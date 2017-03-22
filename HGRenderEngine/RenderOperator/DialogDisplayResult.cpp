// DialogDisplayResult.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DialogDisplayResult.h"
#include "afxdialogex.h"


// DialogDisplayResult �Ի���

IMPLEMENT_DYNAMIC(DialogDisplayResult, CDialogEx)

DialogDisplayResult::DialogDisplayResult(CWnd* pParent /*=NULL*/)
	: DialogPlus(DialogDisplayResult::IDD, pParent)
{

}

DialogDisplayResult::~DialogDisplayResult()
{
}

void DialogDisplayResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogDisplayResult, CDialogEx)
	ON_WM_SIZING()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// DialogDisplayResult ��Ϣ�������


void DialogDisplayResult::OnSizing(UINT fwSide, LPRECT pRect)
{
	DialogPlus::OnSizing(fwSide, pRect);
}


void DialogDisplayResult::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect);
	GetDlgItem(IDC_BORDER_WIN)->MoveWindow(rect);
	
}
