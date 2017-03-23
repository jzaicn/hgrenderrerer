#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include <map>
// DialogRenderSettings 对话框
//#include "ElaraHomeAPI.h"
#include "ButtonPickColor.h"
#include "DialogPlus.h"
#include "resource.h"

#include "HG_Exposure.h"
#include "HG_SkyLight.h"
#include "HG_SunLight.h"

class DialogRenderSettings : public DialogPlus
{
	DECLARE_DYNAMIC(DialogRenderSettings)

public:
	DialogRenderSettings(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogRenderSettings();

// 对话框数据
	enum { IDD = IDD_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	void initFromSetting();

	void initFromTable();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	void setDialogTable(int _father_macro, CString _type,int _control_marco ,CString _cn_name ,CString _en_name, int _second_marco );
	void setCheckBox(CString _cn_name ,CString _en_name,int _silder, int _edit ){};

	afx_msg void OnEditOK();
	afx_msg void OnCheckBtn();

	afx_msg void OnBnClickedSunColorBtn();
	afx_msg void OnBnClickedHdrFileBtn();	

	HG_SunLight get_SunLight();
	void set_SunLight(HG_SunLight sun_light);

	HG_SkyLight get_SkyLight();
	void set_SkyLight(HG_SkyLight sky_light);
	
	HG_Exposure get_Exposure();
	void set_Exposure(HG_Exposure exposure);


	void set_color_uint(UINT macro,UINT color);
	UINT get_color_uint(UINT macro);


	void set_button_text(UINT macro,std::string text);
	std::string get_button_text(UINT macro);

private:
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

	ButtonPickColor m_pickColor;
};
