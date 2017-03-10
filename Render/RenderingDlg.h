#pragma once
#include "resource.h"
// RenderingDlg �Ի���
#include "DialogPlus.h"
#include "RenderSettings.h"
#include "ImageSettings.h"
#include "RenderToolBar.h"
#include "DisplayResult.h"


class RenderingDlg : public DialogPlus
{
	DECLARE_DYNAMIC(RenderingDlg)

public:
	RenderingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RenderingDlg();

// �Ի�������
	enum { IDD = IDD_RENDERINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:	
	CScrollBar m_settingScroll;				// �Ӵ��ڹ�����


	DisplayResult displayResultDlg;				// ��ͼ�Ի���
	CRect m_displayResultDlgRect;				// ��ͼ�Ի�������
	CRect m_displayResultDlgContainerRect;		// ��ͼ��Χ����

	RenderToolBar toolBarDlg;				// �������Ի���
	CRect m_toolBarDlgRect;					// �������Ի�������
	CRect m_toolBarDlgContainerRect;		// ��������Χ����


	ImageSettings imageSettingDlg;			// ͼƬ���öԻ���
	CRect m_imageSettingDlgRect;			// ͼƬ���öԻ�������
	CRect m_imageSettingDlgContainerRect;	// ͼƬ���ð�Χ����


	RenderSettings paramSettingDlg;			// �������öԻ���
	CRect m_paramSettingDlgRect;			// �������öԻ�������
	CRect m_paramSettingDlgContainerRect;	// �������ð�Χ����



	static UINT indicators[];				//״̬������
	CStatusBar   m_wndStatusBar;			//״̬��
	
	
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	void OnCancel()	{	CDialogEx::OnCancel();	};
};
