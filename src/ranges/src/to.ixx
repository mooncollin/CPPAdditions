export module cmoon.ranges:to;

import std.core;

namespace cmoon::ranges
{
	template<class T, class R>
	concept container_compatible_range = std::ranges::input_range<R> &&
							   			 std::convertible_to<std::ranges::range_reference_t<R>, T>;

	template<class Container>
	concept reservable_container = std::ranges::sized_range<Container> &&
		requires(Container& c, std::ranges::range_size_t<Container> n)
	{
		c.reserve(n);
		{ c.capacity() } -> std::same_as<decltype(n)>;
		{ c.max_size() } -> std::same_as<decltype(n)>;
	};

	template<class Container, class Reference>
	concept container_insertable =
		requires(Container& c, Reference&& ref)
	{
		c.push_back(std::forward<Reference>(ref));
		c.insert(c.end(), std::forward<Reference>(ref));
	};

	template<class Reference, class C>
	constexpr auto container_inserter(C& c)
	{
		if constexpr (requires { c.push_back(std::declval<Reference>()); })
		{
			return std::back_inserter(c);
		}
		else
		{
			return std::inserter(c, c.end());
		}
	}

	export
	struct from_range_t
	{
		explicit from_range_t() = default;
	};

	export
	inline constexpr from_range_t from_range {};

	struct program_is_ill_formed
	{
		program_is_ill_formed() = delete;
		~program_is_ill_formed() = delete;
		program_is_ill_formed(const program_is_ill_formed&) = delete;
		program_is_ill_formed(program_is_ill_formed&&) = delete;
		program_is_ill_formed& operator=(const program_is_ill_formed&) = delete;
		program_is_ill_formed& operator=(program_is_ill_formed&&) = delete;
	};

	export
	template<class C, std::ranges::input_range R, class... Args>
		requires(!std::ranges::view<C>)
	constexpr C to(R&& r, Args&&... args)
	{
		if constexpr (!std::ranges::input_range<C> || std::convertible_to<std::ranges::range_reference_t<R>,
																		  std::convertible_to<std::ranges::range_reference_t<R>, std::ranges::range_value_t<C>>>)
		{
			if constexpr (std::constructible_from<C, R, Args...>)
			{
				return C(std::forward<R>(r), std::forward<Args>(args)...);
			}
			else if constexpr (std::constructible_from<C, from_range_t, R, Args...>)
			{
				return C(from_range, std::forward<R>(r), std::forward<Args>(args)...);
			}
			else if constexpr (std::ranges::common_range<R> &&
							   requires { typename std::iterator_traits<std::ranges::iterator_t<R>>::iterator_category; } &&
							   std::derived_from<typename std::iterator_traits<std::ranges::iterator_t<R>>::iterator_category> &&
							   std::constructible_from<C, std::ranges::iterator_t<R>, std::ranges::sentinel_t<R>, Args...>)
			{
				return C(std::ranges::begin(r), std::ranges::end(r), std::forward<Args>(args)...);
			}
			else if constexpr (std::constructible_from<C, Args...> &&
							   container_insertable<C, std::ranges::range_reference_t<R>>)
			{
				C c(std::forward<Args>(args)...);
				if constexpr (std::ranges::sized_range<R> && reservable_container<C>)
				{
					c.reserve(static_cast<std::ranges::range_size_t<C>>(std::ranges::size(r)));
				}
				std::ranges::copy(r, container_inserter<std::ranges::range_reference_t<R>>(c));
			}
			else if constexpr (std::ranges::input_range<std::ranges::range_reference_t<C>>)
			{
				return to<C>(r | std::views::transform([](auto&& elem) {
					return to<std::ranges::range_value_t<C>>(std::forward<decltype(elem)>(elem));
				}), std::forward<Args>(args)...);
			}
			else
			{
				return program_is_ill_formed{};
			}
		}
		else if constexpr (std::ranges::input_range<std::ranges::range_reference_t<C>>)
		{
			return to<C>(r | std::views::transform([](auto&& elem) {
				return to<std::ranges::range_value_t<C>>(std::forward<decltype(elem)>(elem));
			}), std::forward<Args>(args)...);
		}
		else
		{
			return program_is_ill_formed{};
		}
	}

	export
	template<template<class...> class C, std::ranges::input_range R, class... Args>
	constexpr auto to(R&& r, Args&&... args)
	{
		if constexpr (requires{ C(std::declval<R>(), std::declval<Args>()...); })
		{
			return to<decltype(C(std::declval<R>(), std::declval<Args>()...))>(std::forward<R>(r), std::forward<Args>(args)...);
		}
		else
		{
			struct input_iterator_helper
			{
				using iterator_catgory = std::input_iterator_tag;
				using value_type = std::ranges::range_value_t<R>;
				using difference_type = std::ptrdiff_t;
				using pointer = std::add_pointer_t<std::ranges::range_reference_t<R>>;
				using reference = std::ranges::range_reference_t<R>;

				reference operator*() const;
				pointer operator->() const;
				input_iterator_helper& operator++();
				input_iterator_helper& operator++(int);
				bool operator==(const input_iterator_helper&) const;
			};

			if constexpr (requires { C(std::declval<input_iterator_helper>(), std::declval<input_iterator_helper>(), std::declval<Args>()...); })
			{
				return to<decltype(C(std::declval<input_iterator_helper>(), std::declval<input_iterator_helper>(), std::declval<Args>()...))>(std::forward<R>(r), std::forward<Args>(args)...);
			}
			else
			{
				return program_is_ill_formed{};
			}
		}
	}

	// TODO: when I get std::range_adapter_closure
	// export
	// template<class C, class... Args>
	// 	requires(!std::ranges::view<C>)
	// constexpr auto to(Args&&... args)
	// {

	// }

	// export
	// template<template<class...> class C, class... Args>
	// constexpr auto to(Args&&... args)
	// {
		
	// }
}