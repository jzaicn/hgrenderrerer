
// RenderOperator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������



// CRenderOperatorApp:
// �йش����ʵ�֣������ RenderOperator.cpp
//

class CRenderOperatorApp : public CWinApp
{
public:
	CRenderOperatorApp();


	virtual int ExitInstance();

	// ��д
public:
	virtual BOOL InitInstance();
	ULONG_PTR gdiplusToken;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRenderOperatorApp theApp;