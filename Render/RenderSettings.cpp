// RenderSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "RenderSettings.h"
#include "afxdialogex.h"


// RenderSettings 对话框

IMPLEMENT_DYNAMIC(RenderSettings, CDialogEx)

RenderSettings::RenderSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(RenderSettings::IDD, pParent)
	, m_expouse_control(FALSE)
	{

}

RenderSettings::~RenderSettings()
{
}

void RenderSettings::DoDataExchange(CDataExchange* pDX)
{
CDialogEx::DoDataExchange(pDX);
DDX_Check(pDX, IDC_EXPOUSE_CONTROL, m_expouse_control);
	}


BEGIN_MESSAGE_MAP(RenderSettings, CDialogEx)
END_MESSAGE_MAP()


// RenderSettings 消息处理程序
