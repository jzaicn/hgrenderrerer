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
	afx_msg virtual LRESULT OnRenderImageUpdate(WPARAM w,LPARAM l);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	CRect m_oldRect;
	CRect m_newRect;

	bool m_bDragging;									//是否正在拖拽中
	bool m_isDrawingImage;								//是否正在绘制，是的话不可更改cur_image
	Gdiplus::Image* m_cur_image;						//当前绘制图片
	Gdiplus::Image* m_back_image;						//缓冲图片
	float m_fViewingScale;								//图片缩放比例
	POINT m_ptDistanceBetweenViewingAndDiagramCenter;	//绘制起始坐标
	POINT m_ptDragStartPos;								//拖动变化位置
	
	//TODO: 图片恢复缩放比

	//////////////////////////////////////////////////////////////////////////
	// 自定义消息路由
public:
	// 渲染图片更新
	void setScale(float scale);
	float minScale();
	float maxScale();
	float stepScale();
};
