#pragma once


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

private:
	//////////////////////////////////////////////////////////////////////////
	//                                曝光控制
	// 曝光控制
	BOOL m_expouse_control;
	// 曝光值
	int m_exposure_silder;
	// 高光
	int m_high_light_silder;
	// 中间调
	int m_half_tone_silder;
	// 阴影
	int m_shadow_slider;
	// 饱和度
	int m_saturation_slider;
	// 白平衡
	int m_white_balance_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                天光控制
	// 天光控制
	BOOL m_sky_light_control;
	// 天光强度
	int m_sky_light_intensity_slider;
	// 环境HDR
	CComboBox m_hdr_combo;
	// 环境HDR
	CString m_hdr_string;
	// 环境旋转
	int m_hdr_rotate_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                  阳光控制
	// 阳光控制
	BOOL m_sun_control;
	// 阳光强度
	int m_sun_light_intensity_slider;
	// 阳光颜色
	CButton m_sun_color_btn;
	// 软阴影
	int m_soft_shadow_slider;
	// 太阳角度
	int m_sun_angle_slider;
	// 太阳高度
	int m_sun_hight_slider;
};
