#include "StdAfx.h"
#include "HG_ExportOptions.h"
#include <stdexcept>

HG_ExportOptions::HG_ExportOptions(void)
{
	m_base85_encoding = true;
	m_left_handed = false;
	set_exportOption(create());
}


HG_ExportOptions::~HG_ExportOptions(void)
{
	if (get_exportOption())
	{
		free(get_exportOption());
		set_exportOption(NULL);
	}
}

EH_ExportOptions* HG_ExportOptions::create()
{
	EH_ExportOptions* exportOption = (EH_ExportOptions*)(malloc(sizeof(EH_ExportOptions)));
	if (!exportOption)
	{
		throw std::runtime_error("EH_ExportOptions ´´½¨Ê§°Ü");
	}
	saveTo(*exportOption);
	return exportOption;
}


void HG_ExportOptions::loadFrom(const EH_ExportOptions& option)
{
	m_base85_encoding = option.base85_encoding;
	m_left_handed = option.left_handed;
}


void HG_ExportOptions::saveTo(_Out_ EH_ExportOptions& option)
{
	option.base85_encoding = m_base85_encoding;
	option.left_handed = m_left_handed;
}
