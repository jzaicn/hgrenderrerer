
// RenderRun.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRenderRunApp:
// �йش����ʵ�֣������ RenderRun.cpp
//

class CRenderRunApp : public CWinApp
{
public:
	CRenderRunApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRenderRunApp theApp;