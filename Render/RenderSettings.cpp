// RenderSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "RenderSettings.h"
#include "afxdialogex.h"


// RenderSettings 对话框

IMPLEMENT_DYNAMIC(RenderSettings, CDialogEx)

RenderSettings::RenderSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(RenderSettings::IDD, pParent)
	//////////////////////////////////////////////////////////////////////////
	//                                曝光控制
	, m_expouse_control(TRUE)			// 曝光控制
	, m_exposure_silder(-100)			//曝光值 默认-1
	, m_high_light_silder(5)			// 高光
	, m_half_tone_silder(100)			// 中间调
	, m_shadow_slider(10)				// 阴影
	, m_saturation_slider(130)			// 饱和度
	, m_white_balance_slider(650)		// 白平衡

	//////////////////////////////////////////////////////////////////////////
	//                                天光控制
	, m_sky_light_control(TRUE)			// 天光控制
	, m_sky_light_intensity_slider(200)	// 天光强度
	, m_hdr_string(_T(""))
	, m_hdr_rotate_slider(0)			// 环境旋转

	//////////////////////////////////////////////////////////////////////////
	//                                  阳光控制
	, m_sun_control(TRUE)				// 天光控制
	, m_sun_light_intensity_slider(100)	// 阳光强度
	, m_soft_shadow_slider(10)			// 软阴影
	, m_sun_angle_slider(0)				// 太阳角度
	, m_sun_hight_slider(20)			// 太阳高度
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
DDX_Check(pDX, IDC_EXPOUSE_CONTROL, m_expouse_control);			// 曝光控制

DDX_Slider(pDX, IDC_EXPOSURE_SLIDER, m_exposure_silder);		//曝光值
DDV_MinMaxInt(pDX, m_exposure_silder,RANGE(-6, 16, 0.01));		//曝光值-6~16

DDX_Slider(pDX, IDC_HIGH_LIGHT_SLIDER, m_high_light_silder);	// 高光
DDV_MinMaxInt(pDX, m_high_light_silder, RANGE(0, 1, 0.01));		// 高光 0-1

DDX_Slider(pDX, IDC_HALF_TONE_SLIDER, m_half_tone_silder);		// 中间调
DDV_MinMaxInt(pDX, m_half_tone_silder, RANGE(0.1, 4, 0.01));	// 中间调 0.1-4

DDX_Slider(pDX, IDC_SHADOW_SLIDER, m_shadow_slider);			//阴影
DDV_MinMaxInt(pDX, m_shadow_slider, RANGE(0, 1, 0.01));			//阴影 0-1

DDX_Slider(pDX, IDC_SATURATION_SLIDER, m_saturation_slider);	// 饱和度
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 5, 0.01));		// 饱和度 0-5

DDX_Slider(pDX, IDC_WHITE_BALANCE_SLIDER, m_white_balance_slider);				//白平衡
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(100, 20000, 10));					//白平衡 100-20000

//////////////////////////////////////////////////////////////////////////
//                                天光控制
DDX_Check(pDX, IDC_SKY_LIGHT_CONTROL, m_sky_light_control);		// 天光控制

DDX_Slider(pDX, IDC_SKY_LIGHT_INTENSITY_SLIDER, m_sky_light_intensity_slider);	// 天光强度
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 50, 0.1));						// 天光强度

DDX_Control(pDX, IDC_HDR_COMBO, m_hdr_combo);					// 环境HDR
DDX_CBString(pDX, IDC_HDR_COMBO, m_hdr_string);					// 环境HDR

DDX_Slider(pDX, IDC_HDR_ROTATE_SLIDER, m_hdr_rotate_slider);	// 环境旋转
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 360, 1));		// 环境旋转 0-360

//////////////////////////////////////////////////////////////////////////
//                                  阳光控制
DDX_Check(pDX, IDC_SUN_CONTROL, m_sun_control);					// 阳光控制

DDX_Slider(pDX, IDC_SUN_LIGHT_INTENSITY_SLIDER, m_sun_light_intensity_slider);	// 阳光强度
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 50, 0.1));						// 阳光强度 0-50

DDX_Control(pDX, IDC_SUN_COLOR_BTN, m_sun_color_btn);			// 阳光颜色

DDX_Slider(pDX, IDC_SOFT_SHADOW_SLIDER, m_soft_shadow_slider);	// 阳光软阴影
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 10, 0.1));		// 阳光软阴影 0-10

DDX_Slider(pDX, IDC_SUN_ANGLE_SLIDER, m_sun_angle_slider);		// 太阳角度
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 360, 1));		// 太阳角度 0-360

DDX_Slider(pDX, IDC_SUN_HIGHT_SLIDER, m_sun_hight_slider);		// 太阳高度
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(-90, 90, 1));		// 太阳高度 -90 - 90
}


BEGIN_MESSAGE_MAP(RenderSettings, CDialogEx)
END_MESSAGE_MAP()


// RenderSettings 消息处理程序
