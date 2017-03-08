#pragma once
#include "afxcmn.h"
#include "afxwin.h"


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


private:
	//////////////////////////////////////////////////////////////////////////
	//                                曝光控制
	// 曝光控制
	CButton m_expouse_control;
	// 曝光值
	CSliderCtrl m_exposure_silder;
	// 高光
	CSliderCtrl m_high_light_silder;
	// 中间调
	CSliderCtrl m_half_tone_silder;
	// 阴影
	CSliderCtrl m_shadow_slider;
	// 饱和度
	CSliderCtrl m_saturation_slider;
	// 白平衡
	CSliderCtrl m_white_balance_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                天光控制
	// 天光控制
	CButton m_sky_light_control;
	// 天光强度
	CSliderCtrl m_sky_light_intensity_slider;
	// 环境HDR
	CComboBox m_hdr_combo;
	// 环境旋转
	CSliderCtrl m_hdr_rotate_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                  阳光控制
	// 阳光控制
	CButton m_sun_control;
	// 阳光强度
	CSliderCtrl m_sun_light_intensity_slider;
	// 阳光颜色
	CButton m_sun_color_btn;
	// 软阴影
	CSliderCtrl m_soft_shadow_slider;
	// 太阳角度
	CSliderCtrl m_sun_angle_slider;
	// 太阳高度
	CSliderCtrl m_sun_hight_slider;
};
