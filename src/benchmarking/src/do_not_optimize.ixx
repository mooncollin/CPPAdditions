export module cmoon.benchmarking.do_not_optimize;

import std.core;

namespace cmoon::benchmarking
{
	void use_char_pointer(const volatile char*) noexcept {}

	export
	template<class T>
	inline void do_not_optimize(const T& value) noexcept
	{
		use_char_pointer(&reinterpret_cast<const volatile char&>(value));
		_ReadWriteBarrier();
	}
}