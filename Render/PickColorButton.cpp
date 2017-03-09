// PickColorButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Render.h"
#include "PickColorButton.h"


// PickColorButton

IMPLEMENT_DYNAMIC(PickColorButton, CButton)



PickColorButton::~PickColorButton()
{
}


void PickColorButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴�������Ϣ�����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rcClient;
	//CRect rcWindow;

	//CButton* button = (CButton*)(GetDlgItem(IDC_SUN_COLOR_BTN));
	//button->GetClientRect(rcClient);
	//button->GetWindowRect(rcWindow);
	//ScreenToClient(rcWindow);
	GetClientRect(rcClient);

	//��dcMem��
	COLORREF oldBkColor = dc.GetBkColor();
	dc.FillSolidRect(&rcClient, m_color);
	dc.SetBkColor(oldBkColor);
}

BEGIN_MESSAGE_MAP(PickColorButton, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// PickColorButton ��Ϣ��������


