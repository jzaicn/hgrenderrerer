// RenderSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Render.h"
#include "RenderSettings.h"
#include "afxdialogex.h"


// RenderSettings �Ի���

#define DEFAULT(val,step)\
(int)((float)val/(float)step)

IMPLEMENT_DYNAMIC(RenderSettings, CDialogEx)

RenderSettings::RenderSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(RenderSettings::IDD, pParent)
	//////////////////////////////////////////////////////////////////////////
	//                                �ع����
	, m_expouse_control(TRUE)						// �ع����
	, m_exposure_silder(DEFAULT(-1, 0.01))			//�ع�ֵ Ĭ��-1
	, m_high_light_silder(DEFAULT(0.05, 0.01))		// �߹�
	, m_half_tone_silder(DEFAULT(1, 0.01))			// �м��
	, m_shadow_slider(DEFAULT(0.1, 0.01))			// ��Ӱ
	, m_saturation_slider(DEFAULT(1.3, 0.01))		// ���Ͷ�
	, m_white_balance_slider(DEFAULT(6500, 10))		// ��ƽ��

	//////////////////////////////////////////////////////////////////////////
	//                                ������
	, m_sky_light_control(TRUE)						// ������
	, m_sky_light_intensity_slider(DEFAULT(20, 0.1))// ���ǿ��
	, m_hdr_string(_T(""))
	, m_hdr_rotate_slider(DEFAULT(0, 1))			// ������ת

	//////////////////////////////////////////////////////////////////////////
	//                                  �������
	, m_sun_control(TRUE)							// ������
	, m_sun_light_intensity_slider(DEFAULT(10, 0.1))// ����ǿ��
	, m_soft_shadow_slider(DEFAULT(1, 0.1))			// ����Ӱ
	, m_sun_angle_slider(DEFAULT(0, 1))				// ̫���Ƕ�
	, m_sun_hight_slider(DEFAULT(20, 1))			// ̫���߶�
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
DDX_Check(pDX, IDC_EXPOUSE_CONTROL, m_expouse_control);			// �ع����
DDX_Slider(pDX, IDC_EXPOSURE_SLIDER, m_exposure_silder);		//�ع�ֵ
DDX_Slider(pDX, IDC_HIGH_LIGHT_SLIDER, m_high_light_silder);	// �߹�
DDX_Slider(pDX, IDC_HALF_TONE_SLIDER, m_half_tone_silder);		// �м��
DDX_Slider(pDX, IDC_SHADOW_SLIDER, m_shadow_slider);			//��Ӱ
DDX_Slider(pDX, IDC_SATURATION_SLIDER, m_saturation_slider);	// ���Ͷ�
DDX_Slider(pDX, IDC_WHITE_BALANCE_SLIDER, m_white_balance_slider);				//��ƽ��

//////////////////////////////////////////////////////////////////////////
//                                ������
DDX_Check(pDX, IDC_SKY_LIGHT_CONTROL, m_sky_light_control);		// ������
DDX_Slider(pDX, IDC_SKY_LIGHT_INTENSITY_SLIDER, m_sky_light_intensity_slider);	// ���ǿ��
DDX_Control(pDX, IDC_HDR_COMBO, m_hdr_combo);					// ����HDR
DDX_CBString(pDX, IDC_HDR_COMBO, m_hdr_string);					// ����HDR
DDX_Slider(pDX, IDC_HDR_ROTATE_SLIDER, m_hdr_rotate_slider);	// ������ת

//////////////////////////////////////////////////////////////////////////
//                                  �������
DDX_Check(pDX, IDC_SUN_CONTROL, m_sun_control);					// �������
DDX_Slider(pDX, IDC_SUN_LIGHT_INTENSITY_SLIDER, m_sun_light_intensity_slider);	// ����ǿ��
DDX_Control(pDX, IDC_SUN_COLOR_BTN, m_sun_color_btn);			// ������ɫ
DDX_Slider(pDX, IDC_SOFT_SHADOW_SLIDER, m_soft_shadow_slider);	// ��������Ӱ
DDX_Slider(pDX, IDC_SUN_ANGLE_SLIDER, m_sun_angle_slider);		// ̫���Ƕ�
DDX_Slider(pDX, IDC_SUN_HIGHT_SLIDER, m_sun_hight_slider);		// ̫���߶�



//�����������������ʱ�򿪣��ڶԻ���༭�������ÿؼ���������ʱ�����
#if 1

//////////////////////////////////////////////////////////////////////////
//                               �ع����
DDV_MinMaxInt(pDX, m_exposure_silder,RANGE(-6, 16, 0.01));		//�ع�ֵ-6~16
DDV_MinMaxInt(pDX, m_high_light_silder, RANGE(0, 1, 0.01));		// �߹� 0-1
DDV_MinMaxInt(pDX, m_half_tone_silder, RANGE(0.1, 4, 0.01));	// �м�� 0.1-4
DDV_MinMaxInt(pDX, m_shadow_slider, RANGE(0, 1, 0.01));			//��Ӱ 0-1
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 5, 0.01));		// ���Ͷ� 0-5
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(100, 20000, 10));	//��ƽ�� 100-20000

//////////////////////////////////////////////////////////////////////////
//                                ������
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 50, 0.1));		// ���ǿ��
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 360, 1));		// ������ת 0-360

//////////////////////////////////////////////////////////////////////////
//                                  �������
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 50, 0.1));		// ����ǿ�� 0-50
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 10, 0.1));		// ��������Ӱ 0-10
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(0, 360, 1));		// ̫���Ƕ� 0-360
DDV_MinMaxInt(pDX, m_saturation_slider, RANGE(-90, 90, 1));		// ̫���߶� -90 - 90

#endif

}


BEGIN_MESSAGE_MAP(RenderSettings, CDialogEx)
END_MESSAGE_MAP()


// RenderSettings ��Ϣ�������
