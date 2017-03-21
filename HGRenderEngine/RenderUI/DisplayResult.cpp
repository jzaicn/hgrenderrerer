// DisplayResult.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DisplayResult.h"
#include "afxdialogex.h"


// DisplayResult �Ի���

IMPLEMENT_DYNAMIC(DisplayResult, CDialogEx)

DisplayResult::DisplayResult(CWnd* pParent /*=NULL*/)
	: DialogPlus(DisplayResult::IDD, pParent)
{

}

DisplayResult::~DisplayResult()
{
}

void DisplayResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DisplayResult, CDialogEx)
	ON_WM_SIZING()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// DisplayResult ��Ϣ�������


void DisplayResult::OnSizing(UINT fwSide, LPRECT pRect)
{
	DialogPlus::OnSizing(fwSide, pRect);
}


void DisplayResult::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect);
	GetDlgItem(IDC_BORDER_WIN)->MoveWindow(rect);
	
}
