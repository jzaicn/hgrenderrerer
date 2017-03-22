#pragma once
#include "DialogPlus.h"
#include "resource.h"
// DialogRenderToolBar �Ի���

class DialogRenderToolBar : public DialogPlus
{
	DECLARE_DYNAMIC(DialogRenderToolBar)

public:
	DialogRenderToolBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogRenderToolBar();

// �Ի�������
	enum { IDD = IDD_TOOLBAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedZoomOriginBtn();
	afx_msg void OnBnClickedZoomFitBtn();
};
