#pragma once


#include "common.h"
#include "options.h"

namespace foo
{
	class FOODLLTYPE Server
	{
	public:
		explicit Server(options& opt);
		void Start();
	};
}