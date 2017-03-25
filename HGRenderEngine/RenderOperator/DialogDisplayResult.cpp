// DialogDisplayResult.cpp : 实现文件
//

#include "stdafx.h"

#include "DialogDisplayResult.h"
#include "afxdialogex.h"

using namespace Gdiplus;
// DialogDisplayResult 对话框

IMPLEMENT_DYNAMIC(DialogDisplayResult, CDialogEx)

DialogDisplayResult::DialogDisplayResult(CWnd* pParent /*=NULL*/)
	: DialogPlus(DialogDisplayResult::IDD, pParent)
{
	m_isDrawingImage = false;
	m_cur_image = NULL;
	m_back_image = NULL;
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
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 DialogPlus::OnPaint()

	CRect rcClient,rcDrawArea;
	GetClientRect(rcClient);
	rcDrawArea = rcClient;
	//GetDrawArea(rcDrawArea);
	// = m_displayResultDlgContainerRect;
	//CRect rcDrawArea = m_displayResultDlgContainerRect;
	//GetClientRect(rcClient);
	//

	if (!m_isDrawingImage)
	{
		m_isDrawingImage = true;

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(&dc, rcDrawArea.Width(), rcDrawArea.Height());
		dcMem.SelectObject(&bmpMem);


		Graphics g(dcMem.m_hDC);
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);//GetBkColor(dc.m_hDC);

		g.FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
		g.FillRectangle(&SolidBrush(Color::Black), rcDrawArea.left, rcDrawArea.top, rcDrawArea.Width(), rcDrawArea.Height());


		Image* pPanelImg = m_cur_image;
		if(pPanelImg)
		{
		 	CRect rcImg(rcDrawArea.left - ((int)pPanelImg->GetWidth() - (int)rcDrawArea.Width()) / 2, rcDrawArea.top - ((int)pPanelImg->GetHeight() - (int)rcDrawArea.Height()) / 2, \
		 		rcDrawArea.left - ((int)pPanelImg->GetWidth() - (int)rcDrawArea.Width()) / 2 + pPanelImg->GetWidth(), rcDrawArea.top - ((int)pPanelImg->GetHeight() - (int)rcDrawArea.Height()) / 2 + pPanelImg->GetHeight());
		 	//rcImg.OffsetRect(m_ptDistanceBetweenViewingAndDiagramCenter.x, m_ptDistanceBetweenViewingAndDiagramCenter.y);
		 	rcImg.OffsetRect(0, 0);
		 	CRect rcDrawAreaAndImageInterset;
		 	if(rcDrawAreaAndImageInterset.IntersectRect(rcImg, rcDrawArea))
		 	{
		 		RectF rfDes((REAL)rcDrawAreaAndImageInterset.left, (REAL)rcDrawAreaAndImageInterset.top, (REAL)rcDrawAreaAndImageInterset.Width(), (REAL)rcDrawAreaAndImageInterset.Height());
		 
		 		//CString strTmp;
		 		//strTmp.Format(L"L:%d T:%d", (pPanelImg->GetWidth() - rcDrawArea.Width())/* / 2*/, (pPanelImg->GetHeight() - rcDrawArea.Height()) /*/ 2*/);
		 		//OutputDebugString(strTmp);
		 		//strTmp.Format(L"L:%d T:%d W:%d H:%d\n", rcDrawAreaAndImageInterset.left - rcImg.left, rcDrawAreaAndImageInterset.top - rcImg.top, rcDrawAreaAndImageInterset.Width(), rcDrawAreaAndImageInterset.Height());
		 		//OutputDebugString(strTmp);
		 		//strTmp.Format(L"Scale:%f\n", m_fViewingScale);
		 		//OutputDebugString(strTmp);
		 		//strTmp.Format(L"Img W:%d H:%d\n", pPanelImg->GetWidth(), pPanelImg->GetHeight());
		 		//OutputDebugString(strTmp);
		 		g.DrawImage(pPanelImg, rfDes, rcDrawAreaAndImageInterset.left - rcImg.left, rcDrawAreaAndImageInterset.top - rcImg.top, rcDrawAreaAndImageInterset.Width(), rcDrawAreaAndImageInterset.Height(), UnitPixel);
		 	}
		 
		}

		//g.DrawLine(&Pen(Color::Gray), PointF(rcClient.left, rcClient.bottom-STATUS_BAR_HEIGHT), PointF(rcClient.right, rcClient.bottom-STATUS_BAR_HEIGHT));
		//g.DrawLine(&Pen(Color::White), PointF(rcClient.left, rcClient.bottom-STATUS_BAR_HEIGHT+1), PointF(rcClient.right, rcClient.bottom-STATUS_BAR_HEIGHT+1));
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);

		bmpMem.DeleteObject();
		dcMem.DeleteDC();

		m_isDrawingImage = false;
	}
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