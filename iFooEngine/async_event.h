#pragma once

#include <vector>
#include <boost/asio.hpp>

namespace foo
{
	template <boost::asio::execution::executor Executor>
	class basic_async_event
	{
		using executor_type = Executor;
		explicit basic_async_event(executor_type ex) : ex_(std::move(ex))
		{}
		auto get_executor() const noexcept
		{
			return ex_;
		}

	private:
		Executor ex_;
	};
}