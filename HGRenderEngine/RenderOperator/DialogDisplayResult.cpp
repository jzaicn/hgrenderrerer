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
	ON_WM_SIZE()
END_MESSAGE_MAP()


// DialogDisplayResult ��Ϣ�������



void DialogDisplayResult::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
 	CRect rect;
 	GetClientRect(rect);
	//HACK: �㼶���ڴ�С�仯����ôд�����쳣�׳���������Ƕ�����⣬������Ժ���
	//HACK- RenderOperator.exe �е� 0x788045e5 ������ܵ��쳣: 0xC0000005: ��ȡλ�� 0x0000006c ʱ�������ʳ�ͻ
	//HACK- RenderOperator.exe �е� 0x77cc4383 ������ܵ��쳣: 0xC015000F: ����ͣ�õļ��������Ĳ����������ġ�
	//HACK- RenderOperator.exe �е� 0x77cc4383 ������ܵ��쳣: 0xC015000F: ����ͣ�õļ��������Ĳ����������ġ�
 	GetDlgItem(IDC_BORDER_WIN)->MoveWindow(rect);
	
}


BOOL DialogDisplayResult::OnInitDialog()
{
	DialogPlus::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
