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

private:
	CRect m_clientRect;
	CRect m_oldRect;
	CRect m_newRect;
	
	//////////////////////////////////////////////////////////////////////////
	// �Զ�����Ϣ·��
public:
	// ��ȾͼƬ����
	afx_msg virtual LRESULT OnRenderImageUpdate(WPARAM w,LPARAM l);
};
