#include "StdAfx.h"
#include "RenderUI.h"
#include "RenderingDlg.h"


RenderUI::RenderUI(void)
{
}


RenderUI::~RenderUI(void)
{
}

void RenderUI::showRenderDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	RenderingDlg dlg;
	if( dlg.DoModal() == IDOK )
	{
		return;
	}
}
