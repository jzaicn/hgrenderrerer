// RenderDataExporter.h : RenderDataExporter DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRenderDataExporterApp
// �йش���ʵ�ֵ���Ϣ������� RenderDataExporter.cpp
//

class CRenderDataExporterApp : public CWinApp
{
public:
	CRenderDataExporterApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
