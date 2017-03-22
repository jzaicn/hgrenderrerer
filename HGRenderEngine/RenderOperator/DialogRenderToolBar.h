#pragma once
#include "DialogPlus.h"
#include "resource.h"
// DialogRenderToolBar 对话框

class DialogRenderToolBar : public DialogPlus
{
	DECLARE_DYNAMIC(DialogRenderToolBar)

public:
	DialogRenderToolBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogRenderToolBar();

// 对话框数据
	enum { IDD = IDD_TOOLBAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedZoomOriginBtn();
	afx_msg void OnBnClickedZoomFitBtn();
};
