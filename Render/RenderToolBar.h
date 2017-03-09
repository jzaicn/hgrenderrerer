#pragma once


// RenderToolBar 对话框

class RenderToolBar : public CDialogEx
{
	DECLARE_DYNAMIC(RenderToolBar)

public:
	RenderToolBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RenderToolBar();

// 对话框数据
	enum { IDD = IDD_TOOLBAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	void SetBtnImage(int _btn_marco,int _res_marco);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
