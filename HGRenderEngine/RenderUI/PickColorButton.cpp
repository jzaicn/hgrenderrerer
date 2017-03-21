// PickColorButton.cpp : 实现文件
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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rcClient;
	//CRect rcWindow;

	//CButton* button = (CButton*)(GetDlgItem(IDC_SUN_COLOR_BTN));
	//button->GetClientRect(rcClient);
	//button->GetWindowRect(rcWindow);
	//ScreenToClient(rcWindow);
	GetClientRect(rcClient);

	//用dcMem画
	COLORREF oldBkColor = dc.GetBkColor();
	dc.FillSolidRect(&rcClient, m_color);
	dc.SetBkColor(oldBkColor);
}

BEGIN_MESSAGE_MAP(PickColorButton, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// PickColorButton 消息处理程序



