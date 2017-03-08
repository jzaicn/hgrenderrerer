#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// RenderSettings �Ի���

class RenderSettings : public CDialogEx
{
	DECLARE_DYNAMIC(RenderSettings)

public:
	RenderSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RenderSettings();

// �Ի�������
	enum { IDD = IDD_SETTINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();


private:
	//////////////////////////////////////////////////////////////////////////
	//                                �ع����
	// �ع����
	CButton m_expouse_control;
	// �ع�ֵ
	CSliderCtrl m_exposure_silder;
	// �߹�
	CSliderCtrl m_high_light_silder;
	// �м��
	CSliderCtrl m_half_tone_silder;
	// ��Ӱ
	CSliderCtrl m_shadow_slider;
	// ���Ͷ�
	CSliderCtrl m_saturation_slider;
	// ��ƽ��
	CSliderCtrl m_white_balance_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                ������
	// ������
	CButton m_sky_light_control;
	// ���ǿ��
	CSliderCtrl m_sky_light_intensity_slider;
	// ����HDR
	CComboBox m_hdr_combo;
	// ������ת
	CSliderCtrl m_hdr_rotate_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                  �������
	// �������
	CButton m_sun_control;
	// ����ǿ��
	CSliderCtrl m_sun_light_intensity_slider;
	// ������ɫ
	CButton m_sun_color_btn;
	// ����Ӱ
	CSliderCtrl m_soft_shadow_slider;
	// ̫���Ƕ�
	CSliderCtrl m_sun_angle_slider;
	// ̫���߶�
	CSliderCtrl m_sun_hight_slider;
};
