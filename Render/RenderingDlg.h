#pragma once
#include "resource.h"
// RenderingDlg �Ի���
#include "RenderSettings.h"

class RenderingDlg : public CDialog
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

	
	CScrollBar m_settingScroll;				// �Ӵ��ڹ�����
	CRect m_settingDlgContainerRect;		// �Ӵ��ڰ�Χ����
	CRect m_settingDlgRect;					// �Ӵ��ڶԻ�������
	RenderSettings settingDlg;	
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
