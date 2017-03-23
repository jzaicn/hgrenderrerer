
// RenderOperatorDlg.h : 头文件
//

#pragma once

#include "DialogPlus.h"
#include "DialogDisplayResult.h"
#include "DialogImageSettings.h"
#include "DialogRenderToolBar.h"
#include "DialogRenderSettings.h"

// CRenderOperatorDlg 对话框
class CRenderOperatorDlg : public DialogPlus
{
// 构造
public:
	CRenderOperatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RENDEROPERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:	
	CScrollBar m_settingScroll;				// 子窗口滚动条
	CRect m_oldRect;						// 旧窗口区域
	CRect m_newRect;						// 新窗口区域

	DialogDisplayResult displayResultDlg;			// 绘图对话框
	CRect m_displayResultDlgRect;			// 绘图对话框区域
	CRect m_displayResultDlgContainerRect;	// 绘图包围区域

	DialogRenderToolBar toolBarDlg;				// 工具栏对话框
	CRect m_toolBarDlgRect;					// 工具栏对话框区域
	CRect m_toolBarDlgContainerRect;		// 工具栏包围区域


	DialogImageSettings imageSettingDlg;	// 图片配置对话框
	CRect m_imageSettingDlgRect;			// 图片配置对话框区域
	CRect m_imageSettingDlgContainerRect;	// 图片配置包围区域


	DialogRenderSettings paramSettingDlg;			// 属性配置对话框
	CRect m_paramSettingDlgRect;			// 属性配置对话框区域
	CRect m_paramSettingDlgContainerRect;	// 属性配置包围区域



	static UINT indicators[];				//状态栏文字
	CStatusBar   m_wndStatusBar;			//状态栏

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void OnCancel()	{	CDialogEx::OnCancel();	};
	afx_msg void OnBnClickedButton1();

	//////////////////////////////////////////////////////////////////////////
	// 菜单消息
public:
	//"保存图像"
	afx_msg void menu_save_image();
	//"退出"
	afx_msg void menu_exit();
	//"缩放到原始尺寸"
	afx_msg void menu_zoom_origin();
	//"缩放到适应窗口"
	afx_msg void menu_zoom_fit();
	//"工具栏"
	afx_msg void menu_toolbar();
	//"渲染效果面板"
	afx_msg void menu_param_panel();
	//"渲染效果面板"
	afx_msg void menu_settings_panel();
	//"状态栏"
	afx_msg void menu_status();
	//"恢复默认布局"
	afx_msg void menu_default_display();
	//"帮助信息"
	afx_msg void menu_help();

	//////////////////////////////////////////////////////////////////////////
	// 自定义消息路由
public:
	// 打开图像
	afx_msg virtual LRESULT OnSaveImage(WPARAM w,LPARAM l);
	// 保存图像
	afx_msg virtual LRESULT OnLoadImage(WPARAM w,LPARAM l);
	// 退出
	afx_msg virtual LRESULT OnExit(WPARAM w,LPARAM l);
	// 缩放图像到原始尺寸
	afx_msg virtual LRESULT OnZoomOriginImage(WPARAM w,LPARAM l);
	// 缩放图像到适应窗口
	afx_msg virtual LRESULT OnZoomFitImage(WPARAM w,LPARAM l);
	// 放大图像
	afx_msg virtual LRESULT OnZoomInImage(WPARAM w,LPARAM l);
	// 缩小图像
	afx_msg virtual LRESULT OnZoomOutImage(WPARAM w,LPARAM l);
	// 工具栏 隐藏/显示
	afx_msg virtual LRESULT OnToolbarShowHide(WPARAM w,LPARAM l);
	// 图片尺寸配置  隐藏/显示
	afx_msg virtual LRESULT OnParamShowHide(WPARAM w,LPARAM l);
	// 渲染效果配置  隐藏/显示
	afx_msg virtual LRESULT OnSettingShowHide(WPARAM w,LPARAM l);
	// 渲染效果显示  隐藏/显示
	afx_msg virtual LRESULT OnDisplayShowHide(WPARAM w,LPARAM l);
	// 状态栏  隐藏/显示
	afx_msg virtual LRESULT OnStatusShowHide(WPARAM w,LPARAM l);
	// 恢复默认布局 
	afx_msg virtual LRESULT OnDefaultLayout(WPARAM w,LPARAM l);
	// 保存布局 
	afx_msg virtual LRESULT OnSaveLayout(WPARAM w,LPARAM l);
	// 恢复布局 
	afx_msg virtual LRESULT OnLoadLayout(WPARAM w,LPARAM l);
	// 帮助
	afx_msg virtual LRESULT OnHelp(WPARAM w,LPARAM l);
	// 保存配置
	afx_msg virtual LRESULT OnSaveSettings(WPARAM w,LPARAM l);
	// 读取配置
	afx_msg virtual LRESULT OnLoadSettings(WPARAM w,LPARAM l);
	// 渲染开始
	afx_msg virtual LRESULT OnBegin(WPARAM w,LPARAM l);
	// 渲染停止
	afx_msg virtual LRESULT OnStop(WPARAM w,LPARAM l);
	// 渲染停止
	afx_msg virtual LRESULT OnDone(WPARAM w,LPARAM l);
};
