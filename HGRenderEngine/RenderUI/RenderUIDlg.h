
// RenderUIDlg.h : ͷ�ļ�
//

#pragma once

#include "DialogPlus.h"
#include "RenderSettings.h"
#include "ImageSettings.h"
#include "RenderToolBar.h"
#include "DisplayResult.h"


// CRenderUIDlg �Ի���
class CRenderUIDlg : public DialogPlus
{
// ����
public:
	CRenderUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAIN_RENDERING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	

private:	
	CScrollBar m_settingScroll;				// �Ӵ��ڹ�����
	CRect m_oldRect;						// ��������
	CRect m_newRect;						// ��������

	DisplayResult displayResultDlg;			// ��ͼ�Ի���
	CRect m_displayResultDlgRect;			// ��ͼ�Ի�������
	CRect m_displayResultDlgContainerRect;	// ��ͼ��Χ����

	RenderToolBar toolBarDlg;				// �������Ի���
	CRect m_toolBarDlgRect;					// �������Ի�������
	CRect m_toolBarDlgContainerRect;		// ��������Χ����


	ImageSettings imageSettingDlg;			// ͼƬ���öԻ���
	CRect m_imageSettingDlgRect;			// ͼƬ���öԻ�������
	CRect m_imageSettingDlgContainerRect;	// ͼƬ���ð�Χ����


	RenderSettings paramSettingDlg;			// �������öԻ���
	CRect m_paramSettingDlgRect;			// �������öԻ�������
	CRect m_paramSettingDlgContainerRect;	// �������ð�Χ����



	static UINT indicators[];				//״̬������
	CStatusBar   m_wndStatusBar;			//״̬��

// 
 public:
// 	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
 	virtual void OnCancel()	{	CDialogEx::OnCancel();	};
// 
// 	// ��ͼ��
// 	afx_msg virtual LRESULT OnSaveImage(WPARAM w,LPARAM l);;
// 	// ����ͼ��
// 	afx_msg virtual LRESULT OnLoadImage(WPARAM w,LPARAM l){return 0;};
// 	// �˳�
// 	afx_msg virtual LRESULT OnExit(WPARAM w,LPARAM l){return 0;};
// 	// ����ͼ��ԭʼ�ߴ�
// 	afx_msg virtual LRESULT OnZoomOriginImage(WPARAM w,LPARAM l){return 0;};
// 	// ����ͼ����Ӧ����
// 	afx_msg virtual LRESULT OnZoomFitImage(WPARAM w,LPARAM l){return 0;};
// 	// �Ŵ�ͼ��
// 	afx_msg virtual LRESULT OnZoomInImage(WPARAM w,LPARAM l){return 0;};
// 	// ��Сͼ��
// 	afx_msg virtual LRESULT OnZoomOutImage(WPARAM w,LPARAM l){return 0;};
// 	// ������ ����/��ʾ
// 	afx_msg virtual LRESULT OnToolbarShowHide(WPARAM w,LPARAM l){return 0;};
// 	// ��ȾЧ������  ����/��ʾ
// 	afx_msg virtual LRESULT OnDisplayShowHide(WPARAM w,LPARAM l){return 0;};
// 	// ״̬��  ����/��ʾ
// 	afx_msg virtual LRESULT OnStatusShowHide(WPARAM w,LPARAM l){return 0;};
// 	// �ָ�Ĭ�ϲ��� 
// 	afx_msg virtual LRESULT OnDefaultLayout(WPARAM w,LPARAM l){return 0;};
// 	// ���沼�� 
// 	afx_msg virtual LRESULT OnSaveLayout(WPARAM w,LPARAM l){return 0;};
// 	// �ָ����� 
// 	afx_msg virtual LRESULT OnLoadLayout(WPARAM w,LPARAM l){return 0;};
// 	// ����
// 	afx_msg virtual LRESULT OnHelp(WPARAM w,LPARAM l){return 0;};
// 	// ��������
// 	afx_msg virtual LRESULT OnSaveSettings(WPARAM w,LPARAM l){return 0;};
// 	// ��ȡ����
// 	afx_msg virtual LRESULT OnLoadSettings(WPARAM w,LPARAM l){return 0;};
// 	// ��Ⱦ��ʼ
// 	afx_msg virtual LRESULT OnBegin(WPARAM w,LPARAM l);;
// 	// ��Ⱦֹͣ
// 	afx_msg virtual LRESULT OnStop(WPARAM w,LPARAM l){return 0;};
// 	// ��Ⱦֹͣ
// 	afx_msg virtual LRESULT OnDone(WPARAM w,LPARAM l){return 0;};
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
