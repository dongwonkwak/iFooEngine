#pragma once

#include <concepts>
#include <boost/asio.hpp>

namespace foo
{
	template <typename F>
	concept Sender = boost::asio::execution::is_sender_v<std::decay_t<F>>;
}