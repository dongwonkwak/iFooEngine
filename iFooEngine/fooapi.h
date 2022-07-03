#pragma once

#ifdef DLLEXPORT
#define FOODLLTYPE	__declspec(dllexport)
#else
#define FOODLLTYPE __declspec(dllimport)
#endif

#include "Server.h"


extern "C" FOODLLTYPE foo::Server * CreateServer();
extern "C" FOODLLTYPE void StartServer(foo::Server * server);
extern "C" FOODLLTYPE void StopServer(foo::Server* server);