// DialogDisplayResult.cpp : 实现文件
//

#include "stdafx.h"

#include "DialogDisplayResult.h"
#include "afxdialogex.h"

#include "HgLog/HgLog.h"

using namespace Gdiplus;
// DialogDisplayResult 对话框

IMPLEMENT_DYNAMIC(DialogDisplayResult, CDialogEx)

DialogDisplayResult::DialogDisplayResult(CWnd* pParent /*=NULL*/)
	: DialogPlus(DialogDisplayResult::IDD, pParent)
{
	m_bDragging = false;
	m_isDrawingImage = false;
	m_cur_image = NULL;
	m_back_image = NULL;
	m_ptDistanceBetweenViewingAndDiagramCenter.x = 300;
	m_ptDistanceBetweenViewingAndDiagramCenter.y = 300;
	m_fViewingScale = 1.0;
}

DialogDisplayResult::~DialogDisplayResult()
{
}

void DialogDisplayResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogDisplayResult, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	
	//////////////////////////////////////////////////////////////////////////
	// 自定义消息
	ON_MESSAGE(RENDER_IMAGE_UPDATE,&DialogDisplayResult::OnRenderImageUpdate)	// 渲染图片更新
	ON_WM_MOUSEMOVE()
//	ON_WM_MOUSEWHEEL()
//	ON_WM_MOUSEHWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// DialogDisplayResult 消息处理程序



void DialogDisplayResult::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
 	CRect rect;
 	GetClientRect(rect);
	//HACK: 层级窗口大小变化，这么写会有异常抛出，可能是嵌套问题，不清楚以后解决
	//HACK- RenderOperator.exe 中的 0x788045e5 处最可能的异常: 0xC0000005: 读取位置 0x0000006c 时发生访问冲突
	//HACK- RenderOperator.exe 中的 0x77cc4383 处最可能的异常: 0xC015000F: 正被停用的激活上下文不是最近激活的。
	//HACK- RenderOperator.exe 中的 0x77cc4383 处最可能的异常: 0xC015000F: 正被停用的激活上下文不是最近激活的。
 	GetDlgItem(IDC_BORDER_WIN)->MoveWindow(rect);
	
}


BOOL DialogDisplayResult::OnInitDialog()
{
	DialogPlus::OnInitDialog();
	DialogPlus::registerShareHwnd(GetSafeHwnd());
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DialogDisplayResult::OnPaint()
{
	CPaintDC dc(this); 

	//TODO: bug：调整窗口大小后绘制区域有问题

	//获得绘图区域
	CRect rcClient,rcDrawArea;
	GetClientRect(rcClient);
	rcDrawArea = rcClient;

	//如果资源可用的情况下再绘图
	if (!m_isDrawingImage)
	{
		m_isDrawingImage = true;

		//双缓冲
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(&dc, rcDrawArea.Width(), rcDrawArea.Height());
		dcMem.SelectObject(&bmpMem);


		Graphics g(dcMem.m_hDC);
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);//GetBkColor(dc.m_hDC);

		//绘制背景色
		g.FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
		g.FillRectangle(&SolidBrush(Color::Black), rcDrawArea.left, rcDrawArea.top, rcDrawArea.Width(), rcDrawArea.Height());

		//图像资源
		Image* pPanelImg = m_cur_image;
		if(pPanelImg)
		{
			//偏移值
		 	CRect rcImg(rcDrawArea.left - ((int)pPanelImg->GetWidth() - (int)rcDrawArea.Width()) / 2, rcDrawArea.top - ((int)pPanelImg->GetHeight() - (int)rcDrawArea.Height()) / 2, \
		 		rcDrawArea.left - ((int)pPanelImg->GetWidth() - (int)rcDrawArea.Width()) / 2 + pPanelImg->GetWidth(), rcDrawArea.top - ((int)pPanelImg->GetHeight() - (int)rcDrawArea.Height()) / 2 + pPanelImg->GetHeight());
		 	rcImg.OffsetRect(m_ptDistanceBetweenViewingAndDiagramCenter.x, m_ptDistanceBetweenViewingAndDiagramCenter.y);
		 	
			//绘制指定区域数据
		 	CRect rcDrawAreaAndImageInterset;
		 	if(rcDrawAreaAndImageInterset.IntersectRect(rcImg, rcDrawArea))
		 	{
				//缩放比例
		 		RectF rfDes((REAL)rcDrawAreaAndImageInterset.left, (REAL)rcDrawAreaAndImageInterset.top, (REAL)rcDrawAreaAndImageInterset.Width() * m_fViewingScale, (REAL)rcDrawAreaAndImageInterset.Height() * m_fViewingScale);
		 		g.DrawImage(pPanelImg, rfDes, rcDrawAreaAndImageInterset.left - rcImg.left, rcDrawAreaAndImageInterset.top - rcImg.top, rcDrawAreaAndImageInterset.Width(), rcDrawAreaAndImageInterset.Height(), UnitPixel);
				
		 	}
		 
		}
		//绘制到显示区域
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);

		bmpMem.DeleteObject();
		dcMem.DeleteDC();

		m_isDrawingImage = false;
	}
}

void DialogDisplayResult::OnMouseMove(UINT nFlags, CPoint point)
{
	HGLOG_DEBUG("OnMouseMove");

	if(m_bDragging)
	{
		m_ptDistanceBetweenViewingAndDiagramCenter.x += point.x - m_ptDragStartPos.x;
		m_ptDistanceBetweenViewingAndDiagramCenter.y += point.y - m_ptDragStartPos.y;

		m_ptDragStartPos.x = point.x;
		m_ptDragStartPos.y = point.y;

		CRect clientRect;
		GetClientRect(clientRect);
		InvalidateRect(clientRect);
	}
	DialogPlus::OnMouseMove(nFlags, point);
}


void DialogDisplayResult::OnLButtonDown(UINT nFlags, CPoint point)
{
	HGLOG_DEBUG("OnLButtonDown");
	SetFocus();
	m_bDragging = true;
	m_ptDragStartPos.x = point.x;
	m_ptDragStartPos.y = point.y;

	DialogPlus::OnLButtonDown(nFlags, point);
}


void DialogDisplayResult::OnLButtonUp(UINT nFlags, CPoint point)
{
	HGLOG_DEBUG("OnLButtonUp");
	SetFocus();
	m_bDragging = false;

	DialogPlus::OnLButtonUp(nFlags, point);
}


BOOL DialogDisplayResult::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//TODO: 滚轮放大，应该在鼠标指着的区域为中心
	float fDeltaScale = (((float)zDelta) / 120.0) * stepScale();
	setScale(fDeltaScale);	

	Invalidate();
	return DialogPlus::OnMouseWheel(nFlags, zDelta, pt);
}



BOOL DialogDisplayResult::OnEraseBkgnd(CDC* pDC)
{
	

	//return DialogPlus::OnEraseBkgnd(pDC);
	return TRUE;
}




LRESULT DialogDisplayResult::OnRenderImageUpdate(WPARAM w,LPARAM l)
{
	//马上保存传递过来的图片
	if (m_back_image)
	{
		::delete m_back_image;
	}
	Image* image = (Bitmap*)l;
	//m_back_image = image->Clone();
	m_back_image = image;//传递过来的时候已经new过了，暂时不创建新的
	
	//如果不是在绘制，那么可以替换掉当前cur的图片
	if (!m_isDrawingImage)
	{
		m_isDrawingImage = true;

		::delete m_cur_image;
		m_cur_image = m_back_image;
		m_back_image = NULL;
		
		m_isDrawingImage = false;
	}
	Invalidate();
	return 0;
}

void DialogDisplayResult::setScale(float scale)
{
	if (m_fViewingScale < minScale())
	{
		m_fViewingScale = minScale();
	}
	if (m_fViewingScale > maxScale())
	{
		m_fViewingScale = maxScale();
	}
	m_fViewingScale += scale;
}

float DialogDisplayResult::minScale()
{
	return 0.01;
}

float DialogDisplayResult::maxScale()
{
	return 10.0;
}

float DialogDisplayResult::stepScale()
{
	return 0.1;
}
