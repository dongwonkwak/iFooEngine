#pragma once

#include <exception>
#include <concepts>

namespace foo
{
	template <typename P, typename E = std::exception_ptr>
	concept Receiver =
		requires (P & p, E && e) {
		p.set_error((E&&)e);
		p.set_done();
	};

	template <typename P, class... Vs>
	concept ReceiverOf =
		Receiver<P> && std::invocable<P, Vs...>;
}