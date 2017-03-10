#include "StdAfx.h"
#include "HG_ExportOptions.h"
#include <stdexcept>

HG_ExportOptions::HG_ExportOptions(void)
{
	ExportOption(createExportOptions());
}


HG_ExportOptions::~HG_ExportOptions(void)
{
	if (ExportOption())
	{
		free(ExportOption());
	}
}

EH_ExportOptions* HG_ExportOptions::createExportOptions()
{
	EH_ExportOptions* exportOption = (EH_ExportOptions*)(malloc(sizeof(EH_ExportOptions)));
	if (!exportOption)
	{
		throw std::runtime_error("HG_OtherSettings ´´½¨Ê§°Ü");
	}
	exportOption->base85_encoding = false;
	exportOption->left_handed = false;
	return exportOption;
}
