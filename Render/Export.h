// Export.h
//

#pragma once

#if defined(RENDER_DLL)
#define RENDER_EXP __declspec(dllexport)
#else
#define RENDER_EXP __declspec(dllimport)
#endif
