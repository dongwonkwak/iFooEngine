#pragma once

#include <type_traits>

namespace foo
{
	template <typename T>
	class pending;

	template <typename R, typename... Args>
	class pending<R(Args...)>
	{
		template <typename T> requires(!std::is_same_v<std::decay_t<T>, pending>)
			explicit pending(T&& t);
		//R operator()(Args... args);
	};
}