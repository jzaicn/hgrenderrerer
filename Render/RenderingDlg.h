#pragma once
#include "resource.h"
// RenderingDlg �Ի���

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
};
