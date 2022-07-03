#pragma once

#include <concepts>

namespace foo
{
	namespace sender_base_ns { struct sender_base {}; }
	template <typename S, typename = void>
	struct sender_traits_base
	{
		using execution_sender_traits_base_is_unspecialised = void;
	};

	template <typename S>
	struct sender_traits_base<S,
		typename std::enable_if<
			std::is_base_of<sender_base_ns::sender_base, S>::value
		>::type>
	{

	};
	template <typename S, typename = void, typename = void, typename = void>
	struct has_sender_types : std::false_type
	{
	};

	template <
		template <
			template <typename...> class Tuple,
			template <typename...> class Variant
		> class>
	struct has_value_types
	{
		using type = void;
	};

	template <
		template <
		template <typename...> class Variant
	> class>
	struct has_error_types
	{
		typedef void type;
	};


	template <typename S>
	struct has_sender_types<S,
		typename has_value_types<S::template value_types>::type,
		typename has_error_types<S::template error_types>::type,
		typename std::conditional<S::sends_done, void, void>::type> : true_type
	{
	};

	template <typename S>
	struct sender_traits_base<S,
		typename std::enable_if<
		has_sender_types<S>::value
	>::type>
	{
		template <
			template <typename...> class Tuple,
			template <typename...> class Variant>
		using value_types = typename S::template value_types<Tuple, Variant>;

		template <template <typename...> class Variant>
		using error_types = typename S::template error_types<Variant>;
		static_assert(bool, sends_done = S::sends_done);
	};

	template <typename S, typename = void>
	struct has_sender_traits : true_type
	{
	};

	

	//template <typename F>
	//concept Sender = is_sender_v<std::decay_t<F>>;
}