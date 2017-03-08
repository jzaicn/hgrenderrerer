// RenderSettings.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "RenderSettings.h"
#include "afxdialogex.h"


// RenderSettings 对话框

#define DEFAULT(val,step)\
(int)((float)val/(float)step)

IMPLEMENT_DYNAMIC(RenderSettings, CDialogEx)

RenderSettings::RenderSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(RenderSettings::IDD, pParent)
	//////////////////////////////////////////////////////////////////////////
	//                                曝光控制
	, m_expouse_control(TRUE)						// 曝光控制
	, m_exposure_silder(DEFAULT(-1, 0.01))			//曝光值 默认-1
	, m_high_light_silder(DEFAULT(0.05, 0.01))		// 高光
	, m_half_tone_silder(DEFAULT(1, 0.01))			// 中间调
	, m_shadow_slider(DEFAULT(0.1, 0.01))			// 阴影
	, m_saturation_slider(DEFAULT(1.3, 0.01))		// 饱和度
	, m_white_balance_slider(DEFAULT(6500, 10))		// 白平衡

	//////////////////////////////////////////////////////////////////////////
	//                                天光控制
	, m_sky_light_control(TRUE)						// 天光控制
	, m_sky_light_intensity_slider(DEFAULT(20, 0.1))// 天光强度
	, m_hdr_string(_T(""))
	, m_hdr_rotate_slider(DEFAULT(0, 1))			// 环境旋转

	//////////////////////////////////////////////////////////////////////////
	//                                  阳光控制
	, m_sun_control(TRUE)							// 天光控制
	, m_sun_light_intensity_slider(DEFAULT(10, 0.1))// 阳光强度
	, m_soft_shadow_slider(DEFAULT(1, 0.1))			// 软阴影
	, m_sun_angle_slider(DEFAULT(0, 1))				// 太阳角度
	, m_sun_hight_slider(DEFAULT(20, 1))			// 太阳高度
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
DDX_Slider(pDX, IDC_HIGH_LIGHT_SLIDER, m_high_light_silder);	// 高光
DDX_Slider(pDX, IDC_HALF_TONE_SLIDER, m_half_tone_silder);		// 中间调
DDX_Slider(pDX, IDC_SHADOW_SLIDER, m_shadow_slider);			//阴影
DDX_Slider(pDX, IDC_SATURATION_SLIDER, m_saturation_slider);	// 饱和度
DDX_Slider(pDX, IDC_WHITE_BALANCE_SLIDER, m_white_balance_slider);				//白平衡

//////////////////////////////////////////////////////////////////////////
//                                天光控制
DDX_Check(pDX, IDC_SKY_LIGHT_CONTROL, m_sky_light_control);		// 天光控制
DDX_Slider(pDX, IDC_SKY_LIGHT_INTENSITY_SLIDER, m_sky_light_intensity_slider);	// 天光强度
DDX_Control(pDX, IDC_HDR_COMBO, m_hdr_combo);					// 环境HDR
DDX_CBString(pDX, IDC_HDR_COMBO, m_hdr_string);					// 环境HDR
DDX_Slider(pDX, IDC_HDR_ROTATE_SLIDER, m_hdr_rotate_slider);	// 环境旋转

//////////////////////////////////////////////////////////////////////////
//                                  阳光控制
DDX_Check(pDX, IDC_SUN_CONTROL, m_sun_control);					// 阳光控制
DDX_Slider(pDX, IDC_SUN_LIGHT_INTENSITY_SLIDER, m_sun_light_intensity_slider);	// 阳光强度
DDX_Control(pDX, IDC_SUN_COLOR_BTN, m_sun_color_btn);			// 阳光颜色
DDX_Slider(pDX, IDC_SOFT_SHADOW_SLIDER, m_soft_shadow_slider);	// 阳光软阴影
DDX_Slider(pDX, IDC_SUN_ANGLE_SLIDER, m_sun_angle_slider);		// 太阳角度
DDX_Slider(pDX, IDC_SUN_HIGHT_SLIDER, m_sun_hight_slider);		// 太阳高度



//下面的内容正常运行时打开，在对话框编辑窗口设置控件关联变量时会出错
#if 1

//////////////////////////////////////////////////////////////////////////
//                               曝光控制
DDV_MinMaxInt(pDX, m_exposure_silder,RANGE(-6, 16, 0.01));		//曝光值-6~16
DDV_MinMaxInt(pDX, m_high_light_silder, RANGE(0, 1, 0.01));		// 高光 0-1
DDV_MinMaxInt(pDX, m_half_tone_silder, RANGE(0.1, 4, 0.01));	// 中间调 0.1-4
DDV_MinMaxInt(pDX, m_shadow_slider, RANGE(0, 1, 0.01));			//阴影 0-1
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 5, 0.01));		// 饱和度 0-5
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(100, 20000, 10));	//白平衡 100-20000

//////////////////////////////////////////////////////////////////////////
//                                天光控制
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 50, 0.1));		// 天光强度
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 360, 1));		// 环境旋转 0-360

//////////////////////////////////////////////////////////////////////////
//                                  阳光控制
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 50, 0.1));		// 阳光强度 0-50
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 10, 0.1));		// 阳光软阴影 0-10
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 360, 1));		// 太阳角度 0-360
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(-90, 90, 1));		// 太阳高度 -90 - 90

#endif

}


BEGIN_MESSAGE_MAP(RenderSettings, CDialogEx)
END_MESSAGE_MAP()


// RenderSettings 消息处理程序
