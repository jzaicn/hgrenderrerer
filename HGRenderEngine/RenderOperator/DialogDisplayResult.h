#pragma once
#include "DialogPlus.h"
#include "resource.h"
// DialogDisplayResult �Ի���

class DialogDisplayResult : public DialogPlus
{
	DECLARE_DYNAMIC(DialogDisplayResult)

public:
	DialogDisplayResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogDisplayResult();

// �Ի�������
	enum { IDD = IDD_DISPLAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
