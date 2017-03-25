// DialogRenderSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogRenderSettings.h"
#include "afxdialogex.h"

#include "XmlHandlePlus/XmlHandlePlus.h"
#include "XmlHandlePlus/tinyxml.h"

#include "HGCode.h"

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

	ON_BN_CLICKED(IDC_EXPOSURE_CONTROL, &DialogRenderSettings::OnCheckBtn)
	ON_BN_CLICKED(IDC_SKY_LIGHT_CONTROL, &DialogRenderSettings::OnCheckBtn)
	ON_BN_CLICKED(IDC_SUN_CONTROL, &DialogRenderSettings::OnCheckBtn)
	ON_BN_CLICKED(IDC_SUN_COLOR_BTN, &DialogRenderSettings::OnBnClickedSunColorBtn)
	ON_BN_CLICKED(IDC_HDR_FILE_BTN, &DialogRenderSettings::OnBnClickedHdrFileBtn)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DialogRenderSettings 消息处理程序
//TODO: 修改重绘部分，使其更新譬如选中状态等
BOOL DialogRenderSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	initFromTable();
	initFromSetting();
	OnCheckBtn();

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
						text.Format(_T("%.2f"),defaultval);
						edit->SetWindowText(text);
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
							combobtn->AddString(HGCode::convert(optItemPlus.getAttr("cn_name").c_str()));
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
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("STATIC"),	IDC_EXPOSURE_STATIC,	_T("曝光值"),	_T("Exposure"),	NULL);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("STATIC"),	IDC_HIGH_LIGHT_STATIC,	_T("高光"),	_T("HighLight"),	NULL);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("STATIC"),	IDC_HALF_TONE_STATIC,	_T("中间调"),	_T("HalfTone"),	NULL);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("STATIC"),	IDC_SHADOW_STATIC,	_T("阴影"),	_T("Shadow"),	NULL);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("STATIC"),	IDC_SATURATION_STATIC,	_T("饱和度"),	_T("Saturation"),	NULL);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("STATIC"),	IDC_WHITE_BALANCE_STATIC,	_T("白平衡"),	_T("WhiteBalance"),	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("STATIC"),	IDC_SKY_LIGHT_INTENSITY_STATIC,	_T("强度"),	_T("SkyIntensity"),	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("STATIC"),	IDC_HDR_STATIC,	_T("环境HDR"),	_T("SkyHDR"),	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("STATIC"),	IDC_HDR_ROTATE_STATIC,	_T("环境旋转"),	_T("HDRRotate"),	NULL);
	setDialogTable(	IDC_SUN_CONTROL,		_T("STATIC"),	IDC_SUN_LIGHT_INTENSITY_STATIC,	_T("强度"),	_T("SunIntensity"),	NULL);
	setDialogTable(	IDC_SUN_CONTROL,		_T("STATIC"),	IDC_SUN_COLOR_STATIC,	_T("颜色"),	_T("SunColor"),	NULL);
	setDialogTable(	IDC_SUN_CONTROL,		_T("STATIC"),	IDC_SOFT_SHADOW_STATIC,	_T("软阴影"),	_T("SoftShadow"),	NULL);
	setDialogTable(	IDC_SUN_CONTROL,		_T("STATIC"),	IDC_SUN_ANGLE_STATIC,	_T("太阳角度"),	_T("Angle"),	NULL);
	setDialogTable(	IDC_SUN_CONTROL,		_T("STATIC"),	IDC_SUN_HEIGHT_STATIC,	_T("太阳高度"),	_T("Height"),	NULL);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("SILDER"),	IDC_EXPOSURE_SLIDER,	_T("曝光值"),	_T("Exposure"),	IDC_EXPOSURE_EDIT);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("SILDER"),	IDC_HIGH_LIGHT_SLIDER,	_T("高光"),	_T("HighLight"),	IDC_HIGH_LIGHT_EDIT);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("SILDER"),	IDC_HALF_TONE_SLIDER,	_T("中间调"),	_T("HalfTone"),	IDC_HALF_TONE_EDIT);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("SILDER"),	IDC_SHADOW_SLIDER,	_T("阴影"),	_T("Shadow"),	IDC_SHADOW_EDIT);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("SILDER"),	IDC_SATURATION_SLIDER,	_T("饱和度"),	_T("Saturation"),	IDC_SATURATION_EDIT);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("SILDER"),	IDC_WHITE_BALANCE_SLIDER,	_T("白平衡"),	_T("WhiteBalance"),	IDC_WHITE_BALANCE_EDIT);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("SILDER"),	IDC_SKY_LIGHT_INTENSITY_SLIDER,	_T("天光强度"),	_T("SkyIntensity"),	IDC_SKY_LIGHT_INTENSITY_EDIT);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("SILDER"),	IDC_HDR_ROTATE_SLIDER,	_T("环境旋转"),	_T("HdrRotate"),	IDC_HDR_ROTATE_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,		_T("SILDER"),	IDC_SUN_LIGHT_INTENSITY_SLIDER,	_T("阳光强度"),	_T("SunIntensity"),	IDC_SUN_LIGHT_INTENSITY_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,		_T("SILDER"),	IDC_SOFT_SHADOW_SLIDER,	_T("软阴影"),	_T("SoftShadow"),	IDC_SOFT_SHADOW_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,		_T("SILDER"),	IDC_SUN_ANGLE_SLIDER,	_T("太阳角度"),	_T("Angle"),	IDC_SUN_ANGLE_EDIT);
	setDialogTable(	IDC_SUN_CONTROL,		_T("SILDER"),	IDC_SUN_HIGHT_SLIDER,	_T("太阳高度"),	_T("Height"),	IDC_SUN_HEIGHT_EDIT);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("EDIT"),	IDC_EXPOSURE_EDIT,	_T("曝光值"),	_T("Exposure"),	IDC_EXPOSURE_SLIDER);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("EDIT"),	IDC_HIGH_LIGHT_EDIT,	_T("高光"),	_T("HighLight"),	IDC_HIGH_LIGHT_SLIDER);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("EDIT"),	IDC_HALF_TONE_EDIT,	_T("中间调"),	_T("HalfTone"),	IDC_HALF_TONE_SLIDER);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("EDIT"),	IDC_SHADOW_EDIT,	_T("阴影"),	_T("Shadow"),	IDC_SHADOW_SLIDER);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("EDIT"),	IDC_SATURATION_EDIT,	_T("饱和度"),	_T("Saturation"),	IDC_SATURATION_SLIDER);
	setDialogTable(	IDC_EXPOSURE_CONTROL,	_T("EDIT"),	IDC_WHITE_BALANCE_EDIT,	_T("白平衡"),	_T("WhiteBalance"),	IDC_WHITE_BALANCE_SLIDER);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("EDIT"),	IDC_SKY_LIGHT_INTENSITY_EDIT,	_T("天光强度"),	_T("SkyIntensity"),	IDC_SKY_LIGHT_INTENSITY_SLIDER);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("EDIT"),	IDC_HDR_ROTATE_EDIT,	_T("环境旋转"),	_T("HdrRotate"),	IDC_HDR_ROTATE_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,		_T("EDIT"),	IDC_SUN_LIGHT_INTENSITY_EDIT,	_T("阳光强度"),	_T("SunIntensity"),	IDC_SUN_LIGHT_INTENSITY_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,		_T("EDIT"),	IDC_SOFT_SHADOW_EDIT,	_T("软阴影"),	_T("SoftShadow"),	IDC_SOFT_SHADOW_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,		_T("EDIT"),	IDC_SUN_ANGLE_EDIT,	_T("太阳角度"),	_T("Angle"),	IDC_SUN_ANGLE_SLIDER);
	setDialogTable(	IDC_SUN_CONTROL,		_T("EDIT"),	IDC_SUN_HEIGHT_EDIT,	_T("太阳高度"),	_T("Height"),	IDC_SUN_HIGHT_SLIDER);
	setDialogTable(	NULL,	_T("CHECK"),	IDC_EXPOSURE_CONTROL,	_T("曝光控制"),	_T("EXPOSUREControl"),	NULL);
	setDialogTable(	NULL,	_T("CHECK"),	IDC_SKY_LIGHT_CONTROL,	_T("天光"),	_T("SkyLightControl"),	NULL);
	setDialogTable(	NULL,	_T("CHECK"),	IDC_SUN_CONTROL,	_T("阳光"),	_T("SunControl"),	NULL);
	setDialogTable(	IDC_SUN_CONTROL,	_T("BUTTON"),	IDC_SUN_COLOR_BTN,	_T("颜色"),	_T("SunColor"),	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("BUTTON"),	IDC_HDR_FILE_BTN,	_T("HDR图片"),	_T("HDRFile"),	NULL);
	setDialogTable(	IDC_SKY_LIGHT_CONTROL,	_T("COMBO"),	IDC_HDR_COMBO,	_T("HDR图片候选"),	_T("HDRFileList"),	NULL);
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
				text.Format(_T("%.2f"),sider->GetPos() * m_step_val.at(settingIndex));
				edit->SetWindowText(text);
			}
		}
	}
	Post(RENDER_CHANGE_SETTINGS);
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
						newValue.Format(_T("%0.2f"),cur_val);
						edit->SetWindowText(newValue);
					}
					if (cur_val < m_minniment.at(settingIndex))
					{
						cur_val = m_minniment.at(settingIndex);
						CString newValue;
						newValue.Format(_T("%0.2f"),cur_val);
						edit->SetWindowText(newValue);
					}

					int pos = (int)(cur_val/m_step_val.at(settingIndex));
					silder->SetPos(pos);
				}
			}
		}
	}
	Post(RENDER_CHANGE_SETTINGS);
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
	Post(RENDER_CHANGE_SETTINGS);
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
		Post(RENDER_CHANGE_SETTINGS);
		Invalidate();
	}
}


void DialogRenderSettings::OnBnClickedHdrFileBtn()
{
	CString fileType = _T("bmp");
	char filterBuffer[100];
	CString filter;
	filter.Format(_T("%s Files (*.%s)|*.%s|All Files (*.*)|*.*||"),fileType,fileType,fileType);
	//HGTools::Convert2FillChar(filter,filterBuffer);

	//CString fileSaveName;
	//fileSaveName.Format(_T("%s.%s"),defaultname,fileType);

	CFileDialog fileDlg (true, fileType, _T(""),
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, HGCode::convert(filterBuffer), this);
	fileDlg.m_ofn.lpstrTitle = HGCode::convert("打开HDR文件"); 
	//fileDlg.m_ofn.lpstrInitialDir = findPath;


	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();

		Post(RENDER_CHANGE_SETTINGS);
	}
	else
	{
		//return "";
	}
}

HG_SunLight DialogRenderSettings::get_SunLight()
{
	HG_SunLight sun_light;

	sun_light.set_sun_enable(			get_check_bool(IDC_SUN_CONTROL));
	sun_light.set_sun_light_intensity(	get_edit_float(IDC_SUN_LIGHT_INTENSITY_EDIT)	);
	sun_light.set_sun_color(			get_color_uint(IDC_SUN_COLOR_BTN));
	sun_light.set_soft_shadow(			get_edit_float(IDC_SOFT_SHADOW_EDIT));
	sun_light.set_sun_angle(			get_edit_float(IDC_SUN_ANGLE_EDIT));
	sun_light.set_sun_height(			get_edit_float(IDC_SUN_HEIGHT_EDIT));


	return sun_light;
}

void DialogRenderSettings::set_SunLight(HG_SunLight sun_light)
{
	set_check_bool(	IDC_SUN_CONTROL,				sun_light.get_sun_enable());
	set_edit_float(	IDC_SUN_LIGHT_INTENSITY_EDIT,	sun_light.get_sun_light_intensity());
	set_color_uint(	IDC_SUN_COLOR_BTN,				sun_light.get_sun_color());
	set_edit_float(	IDC_SOFT_SHADOW_SLIDER,			sun_light.get_soft_shadow());
	set_edit_float(	IDC_SUN_ANGLE_SLIDER,			sun_light.get_sun_angle());
	set_edit_float(	IDC_SUN_HIGHT_SLIDER,			sun_light.get_sun_height());
}

HG_SkyLight DialogRenderSettings::get_SkyLight()
{
	HG_SkyLight sky_light;

	sky_light.set_sky_light_enable(		get_check_bool(IDC_SKY_LIGHT_CONTROL));
	sky_light.set_sky_light_intensity(	get_edit_float(IDC_SKY_LIGHT_INTENSITY_EDIT));
	sky_light.set_hdr(					get_button_text(IDC_HDR_COMBO));
	sky_light.set_hdr_rotate(			get_edit_float(IDC_HDR_ROTATE_EDIT));

	return sky_light;
}

void DialogRenderSettings::set_SkyLight(HG_SkyLight sky_light)
{
	set_check_bool(		IDC_SKY_LIGHT_CONTROL,			sky_light.get_sky_light_enable());
	set_edit_float(		IDC_SKY_LIGHT_INTENSITY_EDIT,	sky_light.get_sky_light_intensity());
	set_button_text(	IDC_HDR_COMBO,					sky_light.get_hdr());
	set_edit_float(		IDC_HDR_ROTATE_EDIT,			sky_light.get_hdr_rotate());
}

HG_Exposure DialogRenderSettings::get_Exposure()
{
	HG_Exposure exposure;

	exposure.set_exposure_enable(	get_check_bool(IDC_SUN_CONTROL));
	exposure.set_exposure(			get_edit_float(IDC_EXPOSURE_EDIT));
	exposure.set_high_light(			get_edit_float(IDC_HIGH_LIGHT_EDIT));
	exposure.set_half_tone(			get_edit_float(IDC_HALF_TONE_EDIT));
	exposure.set_shadow(				get_edit_float(IDC_SHADOW_EDIT));
	exposure.set_saturation(			get_edit_float(IDC_SATURATION_EDIT));
	exposure.set_white_balance(		get_edit_float(IDC_WHITE_BALANCE_EDIT));
	return exposure;
}

void DialogRenderSettings::set_Exposure(HG_Exposure exposure)
{
	set_check_bool(IDC_EXPOSURE_CONTROL,	exposure.get_exposure_enable());
	set_edit_float(IDC_EXPOSURE_EDIT,		exposure.get_exposure());
	set_edit_float(IDC_HIGH_LIGHT_EDIT,		exposure.get_high_light());
	set_edit_float(IDC_HALF_TONE_EDIT,		exposure.get_half_tone());
	set_edit_float(IDC_SHADOW_EDIT,			exposure.get_shadow());
	set_edit_float(IDC_SATURATION_EDIT,		exposure.get_saturation());
	set_edit_float(IDC_WHITE_BALANCE_EDIT,	exposure.get_white_balance());
}

void DialogRenderSettings::set_color_uint(UINT macro,UINT color)
{
	UINT ucolor2 = color;
	COLORREF ref2 = ucolor2;
	m_pickColor.Color(ref2);
}

UINT DialogRenderSettings::get_color_uint(UINT macro)
{
	COLORREF ref1 = m_pickColor.Color();
	UINT ucolor1 = ref1;
	return ucolor1;
}

void DialogRenderSettings::set_button_text(UINT macro,std::string text)
{
	if (checkMacro(macro))
	{
		CString csText = HGCode::convert(text.c_str());
		(GetDlgItem(macro))->SetWindowText(csText);
	}
}

std::string DialogRenderSettings::get_button_text(UINT macro)
{
	if (checkMacro(macro))
	{
		std::string value;
		CString csText;
		(GetDlgItem(macro))->GetWindowText(csText);
		value = HGCode::convert( csText.GetBuffer());
		return value;
	}
	return "";
}

