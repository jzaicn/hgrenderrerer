#pragma once


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

private:
	//////////////////////////////////////////////////////////////////////////
	//                                �ع����
	// �ع����
	BOOL m_expouse_control;
	// �ع�ֵ
	int m_exposure_silder;
	// �߹�
	int m_high_light_silder;
	// �м��
	int m_half_tone_silder;
	// ��Ӱ
	int m_shadow_slider;
	// ���Ͷ�
	int m_saturation_slider;
	// ��ƽ��
	int m_white_balance_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                ������
	// ������
	BOOL m_sky_light_control;
	// ���ǿ��
	int m_sky_light_intensity_slider;
	// ����HDR
	CComboBox m_hdr_combo;
	// ����HDR
	CString m_hdr_string;
	// ������ת
	int m_hdr_rotate_slider;

	//////////////////////////////////////////////////////////////////////////
	//                                  �������
	// �������
	BOOL m_sun_control;
	// ����ǿ��
	int m_sun_light_intensity_slider;
	// ������ɫ
	CButton m_sun_color_btn;
	// ����Ӱ
	int m_soft_shadow_slider;
	// ̫���Ƕ�
	int m_sun_angle_slider;
	// ̫���߶�
	int m_sun_hight_slider;
};
