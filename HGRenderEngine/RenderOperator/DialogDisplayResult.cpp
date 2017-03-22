// DialogDisplayResult.cpp : 实现文件
//

#include "stdafx.h"

#include "DialogDisplayResult.h"
#include "afxdialogex.h"


// DialogDisplayResult 对话框

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
	ON_WM_SIZE()
END_MESSAGE_MAP()


// DialogDisplayResult 消息处理程序



void DialogDisplayResult::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
 	CRect rect;
 	GetClientRect(rect);
	//HACK: 层级窗口大小变化，这么写会有异常抛出，可能是嵌套问题，不清楚以后解决
	//HACK- RenderOperator.exe 中的 0x788045e5 处最可能的异常: 0xC0000005: 读取位置 0x0000006c 时发生访问冲突
	//HACK- RenderOperator.exe 中的 0x77cc4383 处最可能的异常: 0xC015000F: 正被停用的激活上下文不是最近激活的。
	//HACK- RenderOperator.exe 中的 0x77cc4383 处最可能的异常: 0xC015000F: 正被停用的激活上下文不是最近激活的。
 	GetDlgItem(IDC_BORDER_WIN)->MoveWindow(rect);
	
}


BOOL DialogDisplayResult::OnInitDialog()
{
	DialogPlus::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
