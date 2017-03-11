#pragma once

#include "BaseModel.h"
class HG_ExportOptions
{
public:
	HG_ExportOptions(void);
	~HG_ExportOptions(void);

private:
	EH_ExportOptions* create();
	
public:
	void loadFrom(const EH_ExportOptions& option);
	void saveTo(_Out_ EH_ExportOptions& option);

private:
	GETSET(EH_ExportOptions*,exportOption);

	GETSET(bool,base85_encoding);
	GETSET(bool,left_handed);	
};

