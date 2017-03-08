// RenderSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Render.h"
#include "RenderSettings.h"
#include "afxdialogex.h"

#include "XmlHandlePlus.h"
#include "XmlHandlePlus/tinyxml.h"

// RenderSettings �Ի���

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


// RenderSettings ��Ϣ�������

BOOL RenderSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//"�ع����",IDC_EXPOUSE_CONTROL
	setSilderEditTable("�ع�ֵ"  ,"Exposure" , IDC_EXPOSURE_SLIDER, IDC_EXPOSURE_EDIT);
	setSilderEditTable("�߹�"    ,"HighLight" , IDC_HIGH_LIGHT_SLIDER, IDC_HIGH_LIGHT_EDIT);
	setSilderEditTable("�м��"  ,"HalfTone" , IDC_HALF_TONE_SLIDER, IDC_HALF_TONE_EDIT);
	setSilderEditTable("��Ӱ"    ,"Shadow" , IDC_SHADOW_SLIDER, IDC_SHADOW_EDIT);
	setSilderEditTable("���Ͷ�"  ,"Saturation" , IDC_SATURATION_SLIDER, IDC_SATURATION_EDIT);
	setSilderEditTable("��ƽ��"  ,"WhiteBalance" , IDC_WHITE_BALANCE_SLIDER, IDC_WHITE_BALANCE_EDIT);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//"���",IDC_SKY_LIGHT_CONTROL
	setSilderEditTable("���ǿ��","SkyIntensity" , IDC_SKY_LIGHT_INTENSITY_SLIDER, IDC_SKY_LIGHT_INTENSITY_EDIT);
	setSilderEditTable("������ת","HdrRotate" , IDC_HDR_ROTATE_SLIDER, IDC_HDR_ROTATE_EDIT);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//"����",IDC_SUN_CONTROL
	setSilderEditTable("����ǿ��","SunIntensity" , IDC_SUN_LIGHT_INTENSITY_SLIDER, IDC_SUN_LIGHT_INTENSITY_EDIT);
	setSilderEditTable("����Ӱ"  ,"SoftShadow" , IDC_SOFT_SHADOW_SLIDER, IDC_SOFT_SHADOW_EDIT);
	setSilderEditTable("̫���Ƕ�","Angle" , IDC_SUN_ANGLE_SLIDER, IDC_SUN_ANGLE_EDIT);
	setSilderEditTable("̫���߶�","Height" , IDC_SUN_HIGHT_SLIDER, IDC_SUN_HEIGHT_EDIT);

	


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
					//��ȡ���õ� ���ֵ����Сֵ��Ĭ��ֵ������
					m_maximent[index] = atof(node.getAttr("max").c_str());
					m_minniment[index] = atof(node.getAttr("min").c_str());
					m_default_val[index] = atof(node.getAttr("default").c_str());
					m_step_val[index] = atof(node.getAttr("step").c_str());
					float defaultval = atof(node.getAttr("default").c_str());
				
					//�����϶���
					int min = (int)(atof(node.getAttr("min").c_str())/atof(node.getAttr("step").c_str()));
					int max = (int)(atof(node.getAttr("max").c_str())/atof(node.getAttr("step").c_str()));
					int pos = (int)(atof(node.getAttr("default").c_str())/atof(node.getAttr("step").c_str()));
					sider->SetRange(min,max,TRUE);
					sider->SetPos(pos);

					//���ñ༭��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void RenderSettings::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	for (int i = 0; i < m_control_macro.size() ; i++)
	{
		if (GetDlgItem(m_control_macro.at(i)) == (CWnd*)pScrollBar)
		{
			//������ڵ�������ֵ��
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
