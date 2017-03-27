#include "StdAfx.h"
#include "DialogPlus.h"
#include <stdexcept>

IMPLEMENT_DYNAMIC(DialogPlus, CDialogEx)


std::vector<HWND> DialogPlus::m_shareArr;

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

bool DialogPlus::checkMacro(UINT macro)
{
	if (!GetDlgItem(macro))
	{
		throw std::runtime_error("Dialog item ID get fail!");
		return false;
	}
	return true;
}


float DialogPlus::get_edit_float(UINT macro)
{
	if (checkMacro(macro))
	{
		CString text;
		GetDlgItem(macro)->GetWindowText(text);
		float val = _tstof(text);
		return val;
	}
	return 0;
}

void DialogPlus::set_edit_float(UINT macro,float val)
{
	if (checkMacro(macro))
	{
		CString text;
		text.Format(_T("%0.2f"),val);
		GetDlgItem(macro)->SetWindowText(text);
	}
}
bool DialogPlus::get_check_bool(UINT macro)
{
	if (checkMacro(macro))
	{
		bool check = (bool)((CButton*)GetDlgItem(macro))->GetCheck();
		return check;
	}
	return false;
}

void DialogPlus::set_check_bool(UINT macro,bool val)
{
	if (checkMacro(macro))
	{
		((CButton*)GetDlgItem(macro))->SetCheck(val);
	}
}	

float DialogPlus::getAccuracy(float input,unsigned int accuracy /*= 3*/)
{
#define buf_size 100
	//ͨ���������ɾ����ַ��� ��%0.*f��
	char accuracyBuf[buf_size];
	sprintf_s(accuracyBuf,buf_size,"%%0.%df",accuracy);

	//ͨ���������ɶ�Ӧ���ȵ�float�δ�ӡ���
	char outputBuf[buf_size];
	sprintf_s(outputBuf,buf_size,accuracyBuf,input);

	//��ת��float������
	float output = atof(outputBuf);
	return output;
}

int DialogPlus::getAccuracyInt(float input)
{
	return (int)getAccuracy(input,0);
}

