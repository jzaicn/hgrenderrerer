#pragma once
#include "DialogPlus.h"

// DisplayResult �Ի���

class DisplayResult : public DialogPlus
{
	DECLARE_DYNAMIC(DisplayResult)

public:
	DisplayResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DisplayResult();

// �Ի�������
	enum { IDD = IDD_DISPLAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
