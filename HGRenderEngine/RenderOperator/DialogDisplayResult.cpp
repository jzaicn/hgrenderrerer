// DialogDisplayResult.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DialogDisplayResult.h"
#include "afxdialogex.h"

#include "HgLog/HgLog.h"

using namespace Gdiplus;
// DialogDisplayResult �Ի���

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
	// �Զ�����Ϣ
	ON_MESSAGE(RENDER_IMAGE_UPDATE,&DialogDisplayResult::OnRenderImageUpdate)	// ��ȾͼƬ����
	ON_WM_MOUSEMOVE()
//	ON_WM_MOUSEWHEEL()
//	ON_WM_MOUSEHWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// DialogDisplayResult ��Ϣ�������



void DialogDisplayResult::OnSize(UINT nType, int cx, int cy)
{
	DialogPlus::OnSize(nType, cx, cy);
 	CRect rect;
 	GetClientRect(rect);
	//HACK: �㼶���ڴ�С�仯����ôд�����쳣�׳���������Ƕ�����⣬������Ժ���
	//HACK- RenderOperator.exe �е� 0x788045e5 ������ܵ��쳣: 0xC0000005: ��ȡλ�� 0x0000006c ʱ�������ʳ�ͻ
	//HACK- RenderOperator.exe �е� 0x77cc4383 ������ܵ��쳣: 0xC015000F: ����ͣ�õļ��������Ĳ����������ġ�
	//HACK- RenderOperator.exe �е� 0x77cc4383 ������ܵ��쳣: 0xC015000F: ����ͣ�õļ��������Ĳ����������ġ�
 	GetDlgItem(IDC_BORDER_WIN)->MoveWindow(rect);
	
}


BOOL DialogDisplayResult::OnInitDialog()
{
	DialogPlus::OnInitDialog();
	DialogPlus::registerShareHwnd(GetSafeHwnd());
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void DialogDisplayResult::OnPaint()
{
	CPaintDC dc(this); 

	//TODO: bug���������ڴ�С���������������

	//��û�ͼ����
	CRect rcClient,rcDrawArea;
	GetClientRect(rcClient);
	rcDrawArea = rcClient;

	//�����Դ���õ�������ٻ�ͼ
	if (!m_isDrawingImage)
	{
		m_isDrawingImage = true;

		//˫����
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(&dc, rcDrawArea.Width(), rcDrawArea.Height());
		dcMem.SelectObject(&bmpMem);


		Graphics g(dcMem.m_hDC);
		COLORREF colBK = GetSysColor(CTLCOLOR_DLG);//GetBkColor(dc.m_hDC);

		//���Ʊ���ɫ
		g.FillRectangle(&SolidBrush(Color(GetRValue(colBK), GetGValue(colBK), GetBValue(colBK))), rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
		g.FillRectangle(&SolidBrush(Color::Black), rcDrawArea.left, rcDrawArea.top, rcDrawArea.Width(), rcDrawArea.Height());

		//ͼ����Դ
		Image* pPanelImg = m_cur_image;
		if(pPanelImg)
		{
			//ƫ��ֵ
		 	CRect rcImg(rcDrawArea.left - ((int)pPanelImg->GetWidth() - (int)rcDrawArea.Width()) / 2, rcDrawArea.top - ((int)pPanelImg->GetHeight() - (int)rcDrawArea.Height()) / 2, \
		 		rcDrawArea.left - ((int)pPanelImg->GetWidth() - (int)rcDrawArea.Width()) / 2 + pPanelImg->GetWidth(), rcDrawArea.top - ((int)pPanelImg->GetHeight() - (int)rcDrawArea.Height()) / 2 + pPanelImg->GetHeight());
		 	rcImg.OffsetRect(m_ptDistanceBetweenViewingAndDiagramCenter.x, m_ptDistanceBetweenViewingAndDiagramCenter.y);
		 	
			//����ָ����������
		 	CRect rcDrawAreaAndImageInterset;
		 	if(rcDrawAreaAndImageInterset.IntersectRect(rcImg, rcDrawArea))
		 	{
				//���ű���
		 		RectF rfDes((REAL)rcDrawAreaAndImageInterset.left, (REAL)rcDrawAreaAndImageInterset.top, (REAL)rcDrawAreaAndImageInterset.Width() * m_fViewingScale, (REAL)rcDrawAreaAndImageInterset.Height() * m_fViewingScale);
		 		g.DrawImage(pPanelImg, rfDes, rcDrawAreaAndImageInterset.left - rcImg.left, rcDrawAreaAndImageInterset.top - rcImg.top, rcDrawAreaAndImageInterset.Width(), rcDrawAreaAndImageInterset.Height(), UnitPixel);
				
		 	}
		 
		}
		//���Ƶ���ʾ����
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
	//TODO: ���ַŴ�Ӧ�������ָ�ŵ�����Ϊ����
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
	//���ϱ��洫�ݹ�����ͼƬ
	if (m_back_image)
	{
		::delete m_back_image;
	}
	Image* image = (Bitmap*)l;
	//m_back_image = image->Clone();
	m_back_image = image;//���ݹ�����ʱ���Ѿ�new���ˣ���ʱ�������µ�
	
	//��������ڻ��ƣ���ô�����滻����ǰcur��ͼƬ
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
