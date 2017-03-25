// DialogDisplayResult.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DialogDisplayResult.h"
#include "afxdialogex.h"

using namespace Gdiplus;
// DialogDisplayResult �Ի���

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
	// �Զ�����Ϣ
	ON_MESSAGE(RENDER_IMAGE_UPDATE,&DialogDisplayResult::OnRenderImageUpdate)	// ��ȾͼƬ����
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
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� DialogPlus::OnPaint()

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