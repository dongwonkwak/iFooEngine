#include "fooapi.h"


extern "C" FOODLLTYPE foo::Server * CreateServer()
{
	return new foo::Server();
}

extern "C" FOODLLTYPE void StopServer(foo::Server * server)
{
	if (server)
	{
		delete server;
		server = nullptr;
	}
}

extern "C" FOODLLTYPE void StartServer(foo::Server * server)
{
	if (server)
	{

	}
}