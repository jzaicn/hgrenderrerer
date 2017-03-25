#pragma once
#include "DialogPlus.h"
#include "resource.h"
// DialogDisplayResult 对话框

class DialogDisplayResult : public DialogPlus
{
	DECLARE_DYNAMIC(DialogDisplayResult)

public:
	DialogDisplayResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogDisplayResult();

// 对话框数据
	enum { IDD = IDD_DISPLAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();

private:
	CRect m_clientRect;
	CRect m_oldRect;
	CRect m_newRect;
	
	//////////////////////////////////////////////////////////////////////////
	// 自定义消息路由
public:
	// 渲染图片更新
	afx_msg virtual LRESULT OnRenderImageUpdate(WPARAM w,LPARAM l);
};
