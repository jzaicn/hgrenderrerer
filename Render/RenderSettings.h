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
	// 曝光控制
	BOOL m_expouse_control;
	};
