#pragma once


class DialogPlus :public CDialogEx
{
	DECLARE_DYNAMIC(DialogPlus)
public:
	typedef enum
	{
		RENDER_COMMAND_BEGIN = WM_USER,	//渲染相关命令——开始

		RENDER_SAVE_IMAGE,	// 打开图像
		RENDER_LOAD_IMAGE,	// 保存图像
		RENDER_EXIT,	// 退出
		RENDER_ZOOM_ORIGIN_IMAGE,	// 缩放图像到原始尺寸
		RENDER_ZOOM_FIT_IMAGE,	// 缩放图像到适应窗口
		RENDER_ZOOM_IN_IMAGE,	// 放大图像
		RENDER_ZOOM_OUT_IMAGE,	// 缩小图像
		RENDER_TOOLBAR_SHOW_HIDE,	// 工具栏 隐藏/显示
		RENDER_DISPLAY_SHOW_HIDE,	// 渲染效果配置  隐藏/显示
		RENDER_SETTINGS_SHOW_HIDE,	// 渲染配置  隐藏/显示
		RENDER_STATUS_SHOW_HIDE,	// 状态栏  隐藏/显示
		RENDER_DEFAULT_LAYOUT,	// 恢复默认布局 
		RENDER_SAVE_LAYOUT,	// 保存布局 
		RENDER_LOAD_LAYOUT,	// 恢复布局 
		RENDER_HELP,	// 帮助
		RENDER_SAVE_SETTINGS,	// 保存配置
		RENDER_LOAD_SETTINGS,	// 读取配置
		RENDER_CHANGE_SETTINGS,	// 更改配置
		RENDER_BEGIN,	// 渲染开始
		RENDER_STOP,	// 渲染停止
		RENDER_DONE,	// 渲染停止

		RENDER_COMMAND_END,	//渲染相关命令——结束
	}CMD;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DialogPlus();
	DialogPlus(UINT nIDTemplate, CWnd *pParent = NULL);
	DialogPlus(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
	~DialogPlus(void);

//////////////////////////////////////////////////////////////////////////
// 功能函数
public:
	void SetBtnImage(int _btn_marco,int _res_marco);
	virtual void OnOK();
	virtual void OnCancel();
	CRect getOffset(UINT fwSide, LPRECT pRect);
	

	//////////////////////////////////////////////////////////////////////////
	// 公共数据
public:
	HWND ShareHwnd() const { return m_shareHwnd; }
	void ShareHwnd(HWND val) { m_shareHwnd = val; }

	CString SaveImagePath() const { return m_saveImagePath; }
	void SaveImagePath(CString val) { m_saveImagePath = val; }
private:
	static HWND m_shareHwnd;
	
	static CString m_saveImagePath;


};

