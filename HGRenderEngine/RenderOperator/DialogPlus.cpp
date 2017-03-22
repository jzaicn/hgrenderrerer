#include "StdAfx.h"
#include "DialogPlus.h"

IMPLEMENT_DYNAMIC(DialogPlus, CDialogEx)

HWND DialogPlus::m_shareHwnd;

CString DialogPlus::m_saveImagePath;

DialogPlus::DialogPlus(void):CDialogEx()
{
}


DialogPlus::DialogPlus(UINT nIDTemplate, CWnd *pParent /*= NULL*/):CDialogEx(nIDTemplate,pParent)
{

}

DialogPlus::DialogPlus(LPCTSTR lpszTemplateName, CWnd *pParentWnd /*= NULL*/):CDialogEx(lpszTemplateName,pParentWnd)
{

}

DialogPlus::~DialogPlus(void)
{
}

void DialogPlus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DialogPlus, CDialogEx)
END_MESSAGE_MAP()

void DialogPlus::SetBtnImage(int _btn_marco,int _res_marco)
{
	HBITMAP   hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(_res_marco)); // IDB_BITMAP_TESTΪ��ԴͼƬID 
	((CButton *)GetDlgItem(_btn_marco))->SetBitmap(hBitmap);
}

void DialogPlus::OnOK()
{

}

void DialogPlus::OnCancel()
{

}


CRect DialogPlus::getOffset(const CRect& newRect,const CRect& oldRect)
{
	CRect offset = CRect(
		newRect.left - oldRect.left,
		newRect.top - oldRect.top,
		newRect.right - oldRect.right,
		newRect.bottom - oldRect.bottom
		);
	return offset;
}

