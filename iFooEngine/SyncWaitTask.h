#pragma once

#include <coroutine>
#include <semaphore>

namespace foo
{
	template <typename T>
	class SyncWaitTask
	{
		struct Promise
		{
			T* value{ nullptr };
			std::exception_ptr error_;
			std::binary_semaphore semaphore_;
			SyncWaitTask get_return_object() noexcept
			{
				return SyncWaitTask{ *this };
			}
			void unhandled_exception() noexcept
			{
				error_ = std::current_exception();
			}
			auto yield_value(T&& x) noexcept
			{
				value_ = std::addressof(x);
				return final_suspend();
			}
			auto initial_suspend() noexcept
			{
				return std::suspend_always{};
			}
			auto final_suspend() noexcept
			{
				struct Awaitable
				{
					bool await_ready() noexcept
					{
						return false;
					}
					void await_suspend(std::coroutine_handle<Promise> h) noexcept
					{
						h.promise().semaphore_.release();
					}
					void await_resume() noexcept {}
				};
				return Awaitable{};
			}
			void return_void() noexcept { assert(false); }
		};
		std::coroutine_handle<Promise> handle_;
		explicit SyncWaitTask(Promise& p) noexcept
			: handle_{std::coroutine_handle<Promise>::from_promise(p)}
		{}
	public:
		SyncWaitTask(SyncWaitTask&& t) noexcept
			: handle_{ std::exchange(t.handle_, {}) }
		{}
		~SyncWaitTask()
		{
			if (handle_) handle_.destory();
		}

		T&& get()
		{
			auto& p = handle_.promise();

		}
	};
}