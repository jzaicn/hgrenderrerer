#pragma once
#include "DialogPlus.h"
#include "resource.h"
// DialogDisplayResult �Ի���

class DialogDisplayResult : public DialogPlus
{
	DECLARE_DYNAMIC(DialogDisplayResult)

public:
	DialogDisplayResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogDisplayResult();

// �Ի�������
	enum { IDD = IDD_DISPLAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	// ˢ����ȾͼƬ
	afx_msg virtual LRESULT OnRenderImageUpdate(WPARAM w,LPARAM l);
	// ����ͼ��
	afx_msg virtual LRESULT OnRenderImageSave(WPARAM w,LPARAM l);
	// ��ͼ��
	afx_msg virtual LRESULT OnRenderImageLoad(WPARAM w,LPARAM l);
	// ����ͼ��ԭʼ�ߴ�
	afx_msg virtual LRESULT OnZoomOriginImage(WPARAM w,LPARAM l);
	// ����ͼ����Ӧ����
	afx_msg virtual LRESULT OnZoomFitImage(WPARAM w,LPARAM l);
	// �Ŵ�ͼ��
	afx_msg virtual LRESULT OnZoomInImage(WPARAM w,LPARAM l);
	// ��Сͼ��
	afx_msg virtual LRESULT OnZoomOutImage(WPARAM w,LPARAM l);

	INT GetEncoderClsid(const WCHAR *format, CLSID *pClsid);
private:
	CRect m_oldRect;
	CRect m_newRect;

	bool m_bDragging;									//�Ƿ�������ק��
	bool m_isDrawingImage;								//�Ƿ����ڻ��ƣ��ǵĻ����ɸ���cur_image
	Gdiplus::Image* m_cur_image;						//��ǰ����ͼƬ
	Gdiplus::Image* m_back_image;						//����ͼƬ
	float m_fViewingScale;								//ͼƬ���ű���
	POINT m_ptDistanceBetweenViewingAndDiagramCenter;	//������ʼ����
	POINT m_ptDragStartPos;								//�϶��仯λ��
	
	//TODO: ͼƬ�ָ����ű�

	//////////////////////////////////////////////////////////////////////////
	// �Զ�����Ϣ·��
public:
	// ��ȾͼƬ����
	void setScale(float scale);
	float minScale();
	float maxScale();
	float stepScale();
};
