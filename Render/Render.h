// Render.h : Render DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRenderApp
// �йش���ʵ�ֵ���Ϣ������� Render.cpp
//

class CRenderApp : public CWinApp
{
public:
	CRenderApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
