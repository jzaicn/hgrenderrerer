#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include <map>
// RenderSettings 对话框
#include "ElaraHomeAPI.h"
#include "pickcolorbutton.h"

class RenderSettings : public CDialogEx
{
	DECLARE_DYNAMIC(RenderSettings)

public:
	RenderSettings(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RenderSettings();

// 对话框数据
	enum { IDD = IDD_SETTINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	void initFromSetting();

	void initFromTable();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

public:
	//界面表
	std::vector<int> m_father;
	std::vector<CString> m_type;
	std::vector<CString> m_cn_name;
	std::vector<CString> m_en_name;
	std::vector<int> m_control_macro;
	std::vector<int> m_second_macro;

	//配置表
	std::map<int,int> m_bind_marco;	//通过宏查找配置表的index
	std::vector<float> m_maximent;
	std::vector<float> m_minniment;
	std::vector<float> m_default_val;
	std::vector<float> m_step_val;

	std::vector<std::vector<int>> m_switchControlItem;

	
	void setDialogTable(int _father_macro, CString _type,int _control_marco ,CString _cn_name ,CString _en_name, int _second_marco );
	void setCheckBox(CString _cn_name ,CString _en_name,int _silder, int _edit ){};

	afx_msg void OnEditOK();
	afx_msg void OnCheckBtn();

	afx_msg void OnBnClickedSunColorBtn();
	afx_msg void OnBnClickedHdrFileBtn();	
	
	PickColorButton m_pickColor;
};
