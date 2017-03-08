// RenderSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "RenderSettings.h"
#include "afxdialogex.h"

#include "XmlHandlePlus.h"
#include "XmlHandlePlus/tinyxml.h"

// RenderSettings 对话框

#define DEFAULT(val,step)\
(int)((float)val/(float)step)

IMPLEMENT_DYNAMIC(RenderSettings, CDialogEx)

RenderSettings::RenderSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(RenderSettings::IDD, pParent)
{

}

RenderSettings::~RenderSettings()
{
}

#define RANGE(minv,maxv,step)\
(int)((float)minv/(float)step),(int)((float)maxv/(float)step)

void RenderSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(RenderSettings, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS( IDC_EXPOSURE_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_HIGH_LIGHT_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_HALF_TONE_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SHADOW_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SATURATION_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_WHITE_BALANCE_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SKY_LIGHT_INTENSITY_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_HDR_ROTATE_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SUN_LIGHT_INTENSITY_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SOFT_SHADOW_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SUN_ANGLE_EDIT, &RenderSettings::OnEditOK)
	ON_EN_KILLFOCUS( IDC_SUN_HEIGHT_EDIT, &RenderSettings::OnEditOK)

	ON_BN_CLICKED(IDC_EXPOUSE_CONTROL, &RenderSettings::OnBnCheckSwitch)
	ON_BN_CLICKED(IDC_SKY_LIGHT_CONTROL, &RenderSettings::OnBnCheckSwitch)
	ON_BN_CLICKED(IDC_SUN_CONTROL, &RenderSettings::OnBnCheckSwitch)
END_MESSAGE_MAP()


// RenderSettings 消息处理程序

BOOL RenderSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//"曝光控制",IDC_EXPOUSE_CONTROL
	setSilderEditTable("曝光值"  ,"Exposure" , IDC_EXPOSURE_SLIDER, IDC_EXPOSURE_EDIT);
	setSilderEditTable("高光"    ,"HighLight" , IDC_HIGH_LIGHT_SLIDER, IDC_HIGH_LIGHT_EDIT);
	setSilderEditTable("中间调"  ,"HalfTone" , IDC_HALF_TONE_SLIDER, IDC_HALF_TONE_EDIT);
	setSilderEditTable("阴影"    ,"Shadow" , IDC_SHADOW_SLIDER, IDC_SHADOW_EDIT);
	setSilderEditTable("饱和度"  ,"Saturation" , IDC_SATURATION_SLIDER, IDC_SATURATION_EDIT);
	setSilderEditTable("白平衡"  ,"WhiteBalance" , IDC_WHITE_BALANCE_SLIDER, IDC_WHITE_BALANCE_EDIT);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//"天光",IDC_SKY_LIGHT_CONTROL
	setSilderEditTable("天光强度","SkyIntensity" , IDC_SKY_LIGHT_INTENSITY_SLIDER, IDC_SKY_LIGHT_INTENSITY_EDIT);
	setSilderEditTable("环境旋转","HdrRotate" , IDC_HDR_ROTATE_SLIDER, IDC_HDR_ROTATE_EDIT);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//"阳光",IDC_SUN_CONTROL
	setSilderEditTable("阳光强度","SunIntensity" , IDC_SUN_LIGHT_INTENSITY_SLIDER, IDC_SUN_LIGHT_INTENSITY_EDIT);
	setSilderEditTable("软阴影"  ,"SoftShadow" , IDC_SOFT_SHADOW_SLIDER, IDC_SOFT_SHADOW_EDIT);
	setSilderEditTable("太阳角度","Angle" , IDC_SUN_ANGLE_SLIDER, IDC_SUN_ANGLE_EDIT);
	setSilderEditTable("太阳高度","Height" , IDC_SUN_HIGHT_SLIDER, IDC_SUN_HEIGHT_EDIT);

	


	TiXmlDocument doc;
	doc.LoadFile("E:\\HGRENDER\\trunk\\Render\\RenderParam.xml");
	XmlHandlePlus docHandler(&doc);

	std::vector<TiXmlNode*> nodes = docHandler.findAll("/Root/Param/");
	
	for (auto it = nodes.begin(); it != nodes.end() ; it++)
	{
		XmlHandlePlus node(*it);
		if(node.getAttr("type").compare("float") == 0)
		{
			int index = getDataIndex(node.getAttr("en_name").c_str());
			if (index != -1)
			{
				CSliderCtrl* sider = (CSliderCtrl*)(GetDlgItem(m_control_macro.at(index)));
				CEdit* edit = (CEdit*)(GetDlgItem(m_edit_macro.at(index)));
				if (sider && edit)
				{
					//读取配置的 最大值，最小值，默认值，步长
					m_maximent[index] = atof(node.getAttr("max").c_str());
					m_minniment[index] = atof(node.getAttr("min").c_str());
					m_default_val[index] = atof(node.getAttr("default").c_str());
					m_step_val[index] = atof(node.getAttr("step").c_str());
					float defaultval = atof(node.getAttr("default").c_str());
				
					//设置拖动条
					int min = (int)(atof(node.getAttr("min").c_str())/atof(node.getAttr("step").c_str()));
					int max = (int)(atof(node.getAttr("max").c_str())/atof(node.getAttr("step").c_str()));
					int pos = (int)(atof(node.getAttr("default").c_str())/atof(node.getAttr("step").c_str()));
					sider->SetRange(min,max,TRUE);
					sider->SetPos(pos);

					//设置编辑框
					CString text;
					text.Format("%.2f",defaultval);
					edit->SetWindowTextA(text);
				}
			}
		}
		else if (node.getAttr("type").compare("bool") == 0)
		{
			//CSliderCtrl* sider = (CSliderCtrl*)(GetDlgItem(m_control_macro.at(index)));
		}
		else if (node.getAttr("type").compare("color") == 0)
		{
		}
		else if (node.getAttr("type").compare("combo") == 0)
		{
		}
		else if (node.getAttr("type").compare("color") == 0)
		{
		}
	}
	



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void RenderSettings::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	for (int i = 0; i < m_control_macro.size() ; i++)
	{
		if (GetDlgItem(m_control_macro.at(i)) == (CWnd*)pScrollBar)
		{
			//获得正在调整的数值栏
			CSliderCtrl* sider = (CSliderCtrl*)(GetDlgItem(m_control_macro.at(i)));
			CEdit* edit = (CEdit*)(GetDlgItem(m_edit_macro.at(i)));
			if (sider && edit)
			{
				CString text;
				text.Format("%.2f",sider->GetPos() * m_step_val.at(i));
				edit->SetWindowTextA(text);
			}
		}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void RenderSettings::OnEditOK()
{
	for (int i = 0; i < m_control_macro.size() ; i++)
	{
		if (m_type.at(i) == "float")
		{
			CSliderCtrl* silder = (CSliderCtrl*)(GetDlgItem(m_control_macro.at(i)));
			CEdit* edit = (CEdit*)(GetDlgItem(m_edit_macro.at(i)));
			if (silder && edit)
			{
				CString text;
				edit->GetWindowText(text);
				if (text != "")
				{
					float cur_val = _tstof(text);
					if (cur_val > m_maximent.at(i))
					{
						cur_val = m_maximent.at(i);
						CString newValue;
						newValue.Format("%0.2f",cur_val);
						edit->SetWindowText(newValue);
					}
					if (cur_val < m_minniment.at(i))
					{
						cur_val = m_minniment.at(i);
						CString newValue;
						newValue.Format("%&0.2f",cur_val);
						edit->SetWindowText(newValue);
					}
					
					int pos = (int)(cur_val/m_step_val.at(i));
					silder->SetPos(pos);
				}
			}
		}
	}
}



void RenderSettings::OnBnCheckSwitch()
{
	
}
