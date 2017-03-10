#pragma once
class DialogPlus :public CDialogEx
{
public:
	DialogPlus();
	DialogPlus(UINT nIDTemplate, CWnd *pParent = NULL);
	DialogPlus(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
	~DialogPlus(void);

	void SetBtnImage(int _btn_marco,int _res_marco);
	virtual void OnOK();
	virtual void OnCancel();
	CRect getOffset(UINT fwSide, LPRECT pRect);
};

