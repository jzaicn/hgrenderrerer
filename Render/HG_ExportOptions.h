#pragma once

#include "ElaraHomeAPI.h"
class HG_ExportOptions
{
public:
	HG_ExportOptions(void);
	~HG_ExportOptions(void);


	EH_ExportOptions* createExportOptions();
	
	EH_ExportOptions* ExportOption() const { return m_exportOption; }
	void ExportOption(EH_ExportOptions* val) { m_exportOption = val; }
private:
	EH_ExportOptions* m_exportOption;
};

