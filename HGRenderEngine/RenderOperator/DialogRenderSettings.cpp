// DialogRenderSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogRenderSettings.h"
#include "afxdialogex.h"

#include "XmlHandlePlus.h"
#include "XmlHandlePlus/tinyxml.h"

// DialogRenderSettings 对话框

IMPLEMENT_DYNAMIC(DialogRenderSettings, CDialogEx)

DialogRenderSettings::DialogRenderSettings(CWnd* pParent /*=NULL*/)
	: DialogPlus(DialogRenderSettings::IDD, pParent)
{

}

DialogRenderSettings::~DialogRenderSettings()
{
}

void DialogRenderSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUN_COLOR_BTN, m_pickColor);
}

BEGIN_MESSAGE_MAP(DialogRenderSettings, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS( IDC_EXPOSURE_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_HIGH_LIGHT_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_HALF_TONE_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SHADOW_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SATURATION_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_WHITE_BALANCE_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SKY_LIGHT_INTENSITY_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_HDR_ROTATE_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SUN_LIGHT_INTENSITY_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SOFT_SHADOW_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SUN_ANGLE_EDIT, &DialogRenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SUN_HEIGHT_EDIT, &DialogRenderSettings::OnEditOK)

	ON_BN_CLICKED(IDC_EXPOUSE_CONTROL, &DialogRenderSettings::OnCheckBtn)
	ON_BN_CLICKED(IDC_SKY_LIGHT_CONTROL, &DialogRenderSettings::OnCheckBtn)
	ON_BN_CLICKED(IDC_SUN_CONTROL, &DialogRenderSettings::OnCheckBtn)
	ON_BN_CLICKED(IDC_SUN_COLOR_BTN, &DialogRenderSettings::OnBnClickedSunColorBtn)
	ON_BN_CLICKED(IDC_HDR_FILE_BTN, &DialogRenderSettings::OnBnClickedHdrFileBtn)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SUN_COLOR_BTN, &DialogRenderSettings::OnNMCustomdrawSunColorBtn)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DialogRenderSettings 消息处理程序

BOOL DialogRenderSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	initFromTable();
	initFromSetting();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//从外部配置信息初始化
void DialogRenderSettings::initFromSetting()
{
	TiXmlDocument doc;
	doc.LoadFile("E:\\HGRENDER\\trunk\\HGRenderEngine\\Release\\RenderParam.xml");
	XmlHandlePlus docHandler(&doc);

	std::vector<TiXmlNode*> nodes = docHandler.findAll("/Root/Param/");

	for (auto it = nodes.begin(); it != nodes.end() ; it++)
	{
		XmlHandlePlus node(*it);
		if(node.getAttr("type").compare("float") == 0)
		{
			float max = atof(node.getAttr("max").c_str());
			m_maximent.push_back(max);

			float min = atof(node.getAttr("min").c_str());
			m_minniment.push_back(min);

			float defaultval = atof(node.getAttr("default").c_str());
			m_default_val.push_back(defaultval);

			float step = atof(node.getAttr("step").c_str());
			m_step_val.push_back(step);

			//查找相关的表格元素
			for (UINT i = 0;i<m_control_macro.size();i++)
			{
				if (m_en_name.at(i) == node.getAttr("en_name").c_str())
				{
					//设置拖动条
					if (m_type.at(i) == "SILDER")
					{
						int min_pos = (int)(min/step);
						int max_pos = (int)(max/step);
						int cur_pos = (int)(defaultval/step);

						CSliderCtrl* silder = (CSliderCtrl*)(GetDlgItem(m_control_macro.at(i)));
						silder->SetRange(min_pos,max_pos,TRUE);
						silder->SetPos(cur_pos);

						m_bind_marco.insert(std::map<int,int>::value_type(m_control_macro.at(i),(int)(m_step_val.size())-1));
					}
					//设置编辑框
					if(m_type.at(i) == "EDIT")
					{
						CEdit* edit = (CEdit*)(GetDlgItem(m_control_macro.at(i)));

						CString text;
						text.Format("%.2f",defaultval);
						edit->SetWindowTextA(text);
						m_bind_marco.insert(std::map<int,int>::value_type(m_control_macro.at(i),(int)(m_step_val.size())-1));
					}
				}
				
			}
		}
		else if (node.getAttr("type").compare("bool") == 0)
		{
			float defaultval = atof(node.getAttr("default").c_str());

			for (UINT i = 0;i<m_cn_name.size();i++)
			{
				if (m_type.at(i) == "CHECK")
				{
					if (m_en_name.at(i) == node.getAttr("en_name").c_str())
					{
						CButton* check = (CButton*)(GetDlgItem(m_control_macro.at(i)));
						check->SetCheck((int)defaultval);
						OnCheckBtn();
					}
				}

			}

		}
		else if (node.getAttr("type").compare("color") == 0)
		{
			COLORREF defaultColor = atoi(node.getAttr("default").c_str());
			m_pickColor.Color(defaultColor);
		}
		else if (node.getAttr("type").compare("combo") == 0)
		{
			for (UINT i = 0;i<m_cn_name.size();i++)
			{
				if (m_type.at(i) == "COMBO")
				{
					if (m_en_name.at(i) == node.getAttr("en_name").c_str())
					{
						CComboBox* combobtn = (CComboBox*)(GetDlgItem(m_control_macro.at(i)));
						
						std::vector<TiXmlNode*> options = node.findAll("Option");
						for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
						{
							XmlHandlePlus optItemPlus(*optItem);
							combobtn->AddString(optItemPlus.getAttr("cn_name").c_str());
						}
						combobtn->SetCurSel(atoi(node.getAttr("default").c_str()));
					}
				}
			}

		}
	}
}

//从代码表格初始化
void DialogRenderSettings::initFromTable()
{
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"STATIC",	IDC_EXPOSURE_STATIC,	"曝光值",	"Exposure",	NULL);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"STATIC",	IDC_HIGH_LIGHT_STATIC,	"高光",	"HighLight",	NULL);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"STATIC",	IDC_HALF_TONE_STATIC,	"中间调",	"HalfTone",	NULL);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"STATIC",	IDC_SHADOW_STATIC,	"阴影",	"Shadow",	NULL);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"STATIC",	IDC_SATURATION_STATIC,	"饱和度",	"Saturation",	NULL);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"STATIC",	IDC_WHITE_BALANCE_STATIC,	"白平衡",	"WhiteBalance",	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"STATIC",	IDC_SKY_LIGHT_INTENSITY_STATIC,	"强度",	"SkyIntensity",	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"STATIC",	IDC_HDR_STATIC,	"环境HDR",	"SkyHDR",	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"STATIC",	IDC_HDR_ROTATE_STATIC,	"环境旋转",	"HDRRotate",	NULL);
	setDialogTable(	IDC_SUN_CONTROL,	"STATIC",	IDC_SUN_LIGHT_INTENSITY_STATIC,	"强度",	"SunIntensity",	NULL);
	setDialogTable(	IDC_SUN_CONTROL,	"STATIC",	IDC_SUN_COLOR_STATIC,	"颜色",	"SunColor",	NULL);
	setDialogTable(	IDC_SUN_CONTROL,	"STATIC",	IDC_SOFT_SHADOW_STATIC,	"软阴影",	"SoftShadow",	NULL);
	setDialogTable(	IDC_SUN_CONTROL,	"STATIC",	IDC_SUN_ANGLE_STATIC,	"太阳角度",	"Angle",	NULL);
	setDialogTable(	IDC_SUN_CONTROL,	"STATIC",	IDC_SUN_HEIGHT_STATIC,	"太阳高度",	"Height",	NULL);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"SILDER",	IDC_EXPOSURE_SLIDER,	"曝光值",	"Exposure",	IDC_EXPOSURE_EDIT);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"SILDER",	IDC_HIGH_LIGHT_SLIDER,	"高光",	"HighLight",	IDC_HIGH_LIGHT_EDIT);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"SILDER",	IDC_HALF_TONE_SLIDER,	"中间调",	"HalfTone",	IDC_HALF_TONE_EDIT);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"SILDER",	IDC_SHADOW_SLIDER,	"阴影",	"Shadow",	IDC_SHADOW_EDIT);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"SILDER",	IDC_SATURATION_SLIDER,	"饱和度",	"Saturation",	IDC_SATURATION_EDIT);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"SILDER",	IDC_WHITE_BALANCE_SLIDER,	"白平衡",	"WhiteBalance",	IDC_WHITE_BALANCE_EDIT);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"SILDER",	IDC_SKY_LIGHT_INTENSITY_SLIDER,	"天光强度",	"SkyIntensity",	IDC_SKY_LIGHT_INTENSITY_EDIT);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"SILDER",	IDC_HDR_ROTATE_SLIDER,	"环境旋转",	"HdrRotate",	IDC_HDR_ROTATE_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,	"SILDER",	IDC_SUN_LIGHT_INTENSITY_SLIDER,	"阳光强度",	"SunIntensity",	IDC_SUN_LIGHT_INTENSITY_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,	"SILDER",	IDC_SOFT_SHADOW_SLIDER,	"软阴影",	"SoftShadow",	IDC_SOFT_SHADOW_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,	"SILDER",	IDC_SUN_ANGLE_SLIDER,	"太阳角度",	"Angle",	IDC_SUN_ANGLE_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,	"SILDER",	IDC_SUN_HIGHT_SLIDER,	"太阳高度",	"Height",	IDC_SUN_HEIGHT_EDIT);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"EDIT",	IDC_EXPOSURE_EDIT,	"曝光值",	"Exposure",	IDC_EXPOSURE_SLIDER);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"EDIT",	IDC_HIGH_LIGHT_EDIT,	"高光",	"HighLight",	IDC_HIGH_LIGHT_SLIDER);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"EDIT",	IDC_HALF_TONE_EDIT,	"中间调",	"HalfTone",	IDC_HALF_TONE_SLIDER);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"EDIT",	IDC_SHADOW_EDIT,	"阴影",	"Shadow",	IDC_SHADOW_SLIDER);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"EDIT",	IDC_SATURATION_EDIT,	"饱和度",	"Saturation",	IDC_SATURATION_SLIDER);
	setDialogTable(	IDC_EXPOUSE_CONTROL,	"EDIT",	IDC_WHITE_BALANCE_EDIT,	"白平衡",	"WhiteBalance",	IDC_WHITE_BALANCE_SLIDER);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"EDIT",	IDC_SKY_LIGHT_INTENSITY_EDIT,	"天光强度",	"SkyIntensity",	IDC_SKY_LIGHT_INTENSITY_SLIDER);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"EDIT",	IDC_HDR_ROTATE_EDIT,	"环境旋转",	"HdrRotate",	IDC_HDR_ROTATE_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,	"EDIT",	IDC_SUN_LIGHT_INTENSITY_EDIT,	"阳光强度",	"SunIntensity",	IDC_SUN_LIGHT_INTENSITY_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,	"EDIT",	IDC_SOFT_SHADOW_EDIT,	"软阴影",	"SoftShadow",	IDC_SOFT_SHADOW_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,	"EDIT",	IDC_SUN_ANGLE_EDIT,	"太阳角度",	"Angle",	IDC_SUN_ANGLE_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,	"EDIT",	IDC_SUN_HEIGHT_EDIT,	"太阳高度",	"Height",	IDC_SUN_HIGHT_SLIDER);
	setDialogTable(	NULL,	"CHECK",	IDC_EXPOUSE_CONTROL,	"曝光控制",	"ExpouseControl",	NULL);
	setDialogTable(	NULL,	"CHECK",	IDC_SKY_LIGHT_CONTROL,	"天光",	"SkyLightControl",	NULL);
	setDialogTable(	NULL,	"CHECK",	IDC_SUN_CONTROL,	"阳光",	"SunControl",	NULL);
	setDialogTable(	IDC_SUN_CONTROL,	"BUTTON",	IDC_SUN_COLOR_BTN,	"颜色",	"SunColor",	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"BUTTON",	IDC_HDR_FILE_BTN,	"HDR图片",	"HDRFile",	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	"COMBO",	IDC_HDR_COMBO,	"HDR图片候选",	"HDRFileList",	NULL);
}

//拖动拖动条
void DialogRenderSettings::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	for (UINT i = 0; i < m_control_macro.size() ; i++)
	{
		if (GetDlgItem(m_control_macro.at(i)) == (CWnd*)pScrollBar)
		{
			//获得正在调整的数值栏
			CSliderCtrl* sider = (CSliderCtrl*)(GetDlgItem(m_control_macro.at(i)));
			CEdit* edit = (CEdit*)(GetDlgItem(m_second_macro.at(i)));
			if (sider && edit)
			{
				int settingIndex = m_bind_marco[m_control_macro.at(i)];
				CString text;
				text.Format("%.2f",sider->GetPos() * m_step_val.at(settingIndex));
				edit->SetWindowTextA(text);
			}
		}
	}
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_CHANGE_SETTINGS,NULL,NULL);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//设置表格
void DialogRenderSettings::setDialogTable(int _father_macro, CString _type,int _control_marco ,CString _cn_name ,CString _en_name, int _second_marco)
{
	m_father.push_back(_father_macro);
	m_type.push_back(_type);
	m_cn_name.push_back(_cn_name);
	m_en_name.push_back(_en_name);
	m_control_macro.push_back(_control_marco);
	m_second_macro.push_back(_second_marco);
}

//编辑框 动态更改拖动条，和输入约束
void DialogRenderSettings::OnEditOK()
{
	for (UINT i = 0; i < m_control_macro.size() ; i++)
	{
		if (m_type.at(i) == "EDIT")
		{
			CEdit* edit = (CEdit*)(GetDlgItem(m_control_macro.at(i)));
			CSliderCtrl* silder = (CSliderCtrl*)(GetDlgItem(m_second_macro.at(i)));
			if (silder && edit)
			{
				CString text;
				edit->GetWindowText(text);
				if (text != "")
				{
					int settingIndex = m_bind_marco[m_control_macro.at(i)];
					float cur_val = _tstof(text);
					if (cur_val > m_maximent.at(settingIndex))
					{
						cur_val = m_maximent.at(settingIndex);
						CString newValue;
						newValue.Format("%0.2f",cur_val);
						edit->SetWindowText(newValue);
					}
					if (cur_val < m_minniment.at(settingIndex))
					{
						cur_val = m_minniment.at(settingIndex);
						CString newValue;
						newValue.Format("%0.2f",cur_val);
						edit->SetWindowText(newValue);
					}
					
					int pos = (int)(cur_val/m_step_val.at(settingIndex));
					silder->SetPos(pos);
				}
			}
		}
	}
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_CHANGE_SETTINGS,NULL,NULL);
}


//更改选中
void DialogRenderSettings::OnCheckBtn()
{
	for (UINT fatherIndex = 0; fatherIndex< m_control_macro.size() ; fatherIndex++)
	{
		if (m_type.at(fatherIndex) == "CHECK")
		{
			CButton* check = (CButton*)(GetDlgItem(m_control_macro.at(fatherIndex)));

			for (UINT childIndex = 0; childIndex< m_control_macro.size() ; childIndex++)
			{
				if (m_father.at(childIndex) == m_control_macro.at(fatherIndex))
				{
					GetDlgItem(m_control_macro[childIndex])->EnableWindow(check->GetCheck());
				}
			}
		}
	}
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_CHANGE_SETTINGS,NULL,NULL);
}


//选择颜色
void DialogRenderSettings::OnBnClickedSunColorBtn()
{
	CColorDialog m_setClrDlg;
	m_setClrDlg.m_cc.Flags |= CC_FULLOPEN|CC_RGBINIT;   // CC_RGBINIT可以让上次选择的颜色作为初始颜色显示出来
	//m_setClrDlg.m_cc.rgbResult = m_clr;        //记录上次选择的颜色
	if(IDOK ==m_setClrDlg.DoModal())
	{
		COLORREF color = m_setClrDlg.m_cc.rgbResult;            // 保存用户选择的颜色
		m_pickColor.Color(color);
		::PostMessage(ShareHwnd(),DialogPlus::RENDER_CHANGE_SETTINGS,NULL,NULL);
		Invalidate();
	}
}


void DialogRenderSettings::OnBnClickedHdrFileBtn()
{
	CString fileType = "bmp";
	char filterBuffer[100];
	CString filter;
	filter.Format("%s Files (*.%s)|*.%s|All Files (*.*)|*.*||",fileType,fileType,fileType);
	//HGTools::Convert2FillChar(filter,filterBuffer);

	//CString fileSaveName;
	//fileSaveName.Format("%s.%s",defaultname,fileType);

	CFileDialog fileDlg (true, fileType, "",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, filterBuffer, this);
	fileDlg.m_ofn.lpstrTitle = "打开HDR文件"; 
	//fileDlg.m_ofn.lpstrInitialDir = findPath;


	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		
		::PostMessage(ShareHwnd(),DialogPlus::RENDER_CHANGE_SETTINGS,NULL,NULL);
	}
	else
	{
		//return "";
	}
}




