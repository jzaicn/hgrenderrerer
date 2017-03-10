#pragma once
#include "DialogPlus.h"

// DisplayResult 对话框

class DisplayResult : public DialogPlus
{
	DECLARE_DYNAMIC(DisplayResult)

public:
	DisplayResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DisplayResult();

// 对话框数据
	enum { IDD = IDD_DISPLAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
