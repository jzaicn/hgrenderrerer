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


	//////////////////////////////////////////////////////////////////////////
	//                                曝光控制
	// 曝光控制
	DDX_Control(pDX, IDC_EXPOUSE_CONTROL, m_expouse_control);
	// 曝光值
	DDX_Control(pDX, IDC_EXPOSURE_SLIDER, m_exposure_silder);
	// 高光
	DDX_Control(pDX, IDC_HIGH_LIGHT_SLIDER, m_high_light_silder);
	// 中间调
	DDX_Control(pDX, IDC_HALF_TONE_SLIDER, m_half_tone_silder);
	// 阴影
	DDX_Control(pDX, IDC_SHADOW_SLIDER, m_shadow_slider);
	// 饱和度
	DDX_Control(pDX, IDC_SATURATION_SLIDER, m_saturation_slider);
	// 白平衡
	DDX_Control(pDX, IDC_WHITE_BALANCE_SLIDER, m_white_balance_slider);

	//////////////////////////////////////////////////////////////////////////
	//                                天光控制
	// 天光控制
	DDX_Control(pDX, IDC_SKY_LIGHT_CONTROL, m_sky_light_control);
	// 天光强度
	DDX_Control(pDX, IDC_SKY_LIGHT_INTENSITY_SLIDER, m_sky_light_intensity_slider);
	// 环境HDR
	DDX_Control(pDX, IDC_HDR_COMBO, m_hdr_combo);
	// 环境旋转
	DDX_Control(pDX, IDC_HDR_ROTATE_SLIDER, m_hdr_rotate_slider);

	//////////////////////////////////////////////////////////////////////////
	//                                  阳光控制
	// 阳光控制
	DDX_Control(pDX, IDC_SUN_CONTROL, m_sun_control);
	// 阳光强度
	DDX_Control(pDX, IDC_SUN_LIGHT_INTENSITY_SLIDER, m_sun_light_intensity_slider);
	// 阳光颜色
	DDX_Control(pDX, IDC_SUN_COLOR_BTN, m_sun_color_btn);
	// 软阴影
	DDX_Control(pDX, IDC_SOFT_SHADOW_SLIDER, m_soft_shadow_slider);
	// 太阳角度
	DDX_Control(pDX, IDC_SUN_ANGLE_SLIDER, m_sun_angle_slider);
	// 太阳高度
	DDX_Control(pDX, IDC_SUN_HIGHT_SLIDER, m_sun_hight_slider);
}

BEGIN_MESSAGE_MAP(RenderSettings, CDialogEx)
END_MESSAGE_MAP()


// RenderSettings 消息处理程序


BOOL RenderSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TiXmlDocument doc;
	doc.LoadFile("E:\\HGRENDER\\trunk\\Render\\RenderParam.xml");
	XmlHandlePlus docHandler(&doc);

	docHandler.changeDirectoryTo("/Root/Exposure/Switch");
	docHandler.getAttr("default");

	

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
