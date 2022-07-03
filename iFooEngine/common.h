#pragma once

#ifdef DLLEXPORT
#define FOODLLTYPE	__declspec(dllexport)
#else
#define FOODLLTYPE __declspec(dllimport)
#endif