#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>

// RenderSettings 对话框

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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

public:

	std::vector<CString> m_cn_name;
	std::vector<CString> m_en_name;
	std::vector<int> m_control_macro;
	std::vector<int> m_edit_macro;
	std::vector<CString> m_type;
	std::vector<float> m_maximent;
	std::vector<float> m_minniment;
	std::vector<float> m_default_val;
	std::vector<float> m_step_val;

	std::vector<std::vector<int>> m_switchControlItem;

	void setSilderEditTable(CString _cn_name ,CString _en_name,int _silder, int _edit )
	{
		m_cn_name.push_back(_cn_name);
		m_en_name.push_back(_en_name);
		m_control_macro.push_back(_silder);
		m_edit_macro.push_back(_edit);
		
		m_type.push_back("float");
		m_maximent.push_back(0.0);
		m_minniment.push_back(0.0);
		m_default_val.push_back(0.0);
		m_step_val.push_back(0.0);
	}
	void setCheckBox(CString _cn_name ,CString _en_name,int _silder, int _edit ){};

	int getDataIndex(CString _en_name)
	{
		for (int i = 0; i < m_en_name.size() ; i++)
		{
			if(_en_name == m_en_name.at(i))
			{
				return i;
			}
		}
		return -1;
	}

	afx_msg void OnEditOK();
	afx_msg void OnBnCheckSwitch();
};
