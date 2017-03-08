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


	//////////////////////////////////////////////////////////////////////////
	//                                �ع����
	// �ع����
	DDX_Control(pDX, IDC_EXPOUSE_CONTROL, m_expouse_control);
	// �ع�ֵ
	DDX_Control(pDX, IDC_EXPOSURE_SLIDER, m_exposure_silder);
	// �߹�
	DDX_Control(pDX, IDC_HIGH_LIGHT_SLIDER, m_high_light_silder);
	// �м��
	DDX_Control(pDX, IDC_HALF_TONE_SLIDER, m_half_tone_silder);
	// ��Ӱ
	DDX_Control(pDX, IDC_SHADOW_SLIDER, m_shadow_slider);
	// ���Ͷ�
	DDX_Control(pDX, IDC_SATURATION_SLIDER, m_saturation_slider);
	// ��ƽ��
	DDX_Control(pDX, IDC_WHITE_BALANCE_SLIDER, m_white_balance_slider);

	//////////////////////////////////////////////////////////////////////////
	//                                ������
	// ������
	DDX_Control(pDX, IDC_SKY_LIGHT_CONTROL, m_sky_light_control);
	// ���ǿ��
	DDX_Control(pDX, IDC_SKY_LIGHT_INTENSITY_SLIDER, m_sky_light_intensity_slider);
	// ����HDR
	DDX_Control(pDX, IDC_HDR_COMBO, m_hdr_combo);
	// ������ת
	DDX_Control(pDX, IDC_HDR_ROTATE_SLIDER, m_hdr_rotate_slider);

	//////////////////////////////////////////////////////////////////////////
	//                                  �������
	// �������
	DDX_Control(pDX, IDC_SUN_CONTROL, m_sun_control);
	// ����ǿ��
	DDX_Control(pDX, IDC_SUN_LIGHT_INTENSITY_SLIDER, m_sun_light_intensity_slider);
	// ������ɫ
	DDX_Control(pDX, IDC_SUN_COLOR_BTN, m_sun_color_btn);
	// ����Ӱ
	DDX_Control(pDX, IDC_SOFT_SHADOW_SLIDER, m_soft_shadow_slider);
	// ̫���Ƕ�
	DDX_Control(pDX, IDC_SUN_ANGLE_SLIDER, m_sun_angle_slider);
	// ̫���߶�
	DDX_Control(pDX, IDC_SUN_HIGHT_SLIDER, m_sun_hight_slider);
}

BEGIN_MESSAGE_MAP(RenderSettings, CDialogEx)
END_MESSAGE_MAP()


// RenderSettings ��Ϣ�������


BOOL RenderSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TiXmlDocument doc;
	doc.LoadFile("E:\\HGRENDER\\trunk\\Render\\RenderParam.xml");
	XmlHandlePlus docHandler(&doc);

	docHandler.changeDirectoryTo("/Root/Exposure/Switch");
	docHandler.getAttr("default");

	

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
