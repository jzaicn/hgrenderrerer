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
	// �ع����
	BOOL m_expouse_control;
	};
