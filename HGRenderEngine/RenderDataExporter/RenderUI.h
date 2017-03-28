#pragma once
#include "Export.h"
//用于对外提供调用，实际导出数据
class RENDER_EXP RenderUI
{
public:
	RenderUI(void){};
	~RenderUI(void){};

	static void showRenderDlg();

	static void save2file();

};

