#pragma once


// RenderToolBar �Ի���

class RenderToolBar : public CDialogEx
{
	DECLARE_DYNAMIC(RenderToolBar)

public:
	RenderToolBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RenderToolBar();

// �Ի�������
	enum { IDD = IDD_TOOLBAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	void SetBtnImage(int _btn_marco,int _res_marco);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
