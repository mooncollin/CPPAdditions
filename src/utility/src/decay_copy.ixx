export module cmoon.utility:decay_copy;

import std.core;

namespace cmoon
{
	export
	template<class T>
	constexpr std::decay_t<T> decay_copy(T&& v) noexcept(noexcept(static_cast<std::decay_t<T>>(std::forward<T>(v))))
	{
		return static_cast<std::decay_t<T>>(std::forward<T>(v));
	}
}