#pragma once
#include "DialogPlus.h"

// RenderToolBar �Ի���

class RenderToolBar : public DialogPlus
{
	DECLARE_DYNAMIC(RenderToolBar)

public:
	RenderToolBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RenderToolBar();

// �Ի�������
	enum { IDD = IDD_TOOLBAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
