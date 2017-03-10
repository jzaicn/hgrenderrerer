#pragma once

#include "ElaraHomeAPI.h"

class HG_Core
{
public:
	HG_Core(void);
	~HG_Core(void);

	EH_Context* RenderContext() const { return m_renderContext; }
	void RenderContext(EH_Context* val) { m_renderContext = val; }
private:
	EH_Context* m_renderContext;
};

