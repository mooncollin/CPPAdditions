export module cmoon.meta:value_list;

import std.core;

import :type_list;

namespace cmoon::meta
{
	export
	template<auto... Values>
	struct value_list
	{
		template<auto... Values2>
		friend struct value_list;

		public:
			using index_type = std::size_t;
			using types = type_list<decltype(Values)...>;

			template<index_type N>
			using type = typename types::template type<N>;

			static constexpr index_type npos {std::numeric_limits<index_type>::max()};

			[[nodiscard]] static constexpr index_type size() noexcept
			{
				return sizeof...(Values);
			}

			[[nodiscard]] static constexpr bool empty() noexcept
			{
				return size() == 0;
			}
		private:
			template<index_type N, auto Value1, auto... ValueN>
			[[nodiscard]] static constexpr auto get_helper() noexcept
			{
				if constexpr (N == 0)
				{
					return Value1;
				}
				else
				{
					return get_helper<N - 1, ValueN...>();
				}
			}

			template<class T>
			[[nodiscard]] static constexpr bool contains_helper(const T&) noexcept
			{
				return false;
			}

			template<auto Value1, auto... ValueN, class T>
			[[nodiscard]] static constexpr bool contains_helper(const T& item) noexcept
			{
				if constexpr (std::same_as<std::remove_cvref_t<decltype(Value1)>,
										   std::remove_cvref_t<T>>)
				{
					return Value1 == item || contains_helper<ValueN...>(item);
				}
				else
				{
					return contains_helper<ValueN...>(item);
				}
			}
		public:
			template<index_type N>
				requires(N < value_list::size())
			[[nodiscard]] static constexpr auto get() noexcept
			{
				return get_helper<N, Values...>();
			}

			template<class T>
			[[nodiscard]] static constexpr bool contains(const T& item) noexcept
			{
				return contains_helper<Values...>(item);
			}

			[[nodiscard]] static constexpr auto to_tuple() noexcept(std::conjunction_v<std::is_nothrow_copy_constructible<decltype(Values)>...>)
			{
				return std::make_tuple(Values...);
			}

			template<class F>
			[[nodiscard]] static constexpr bool all_of(F&& func) noexcept(std::conjunction_v<std::is_nothrow_invocable<F, decltype(Values)>...>)
			{
				return (std::invoke(func, Values) && ...);
			}

			template<class F>
			[[nodiscard]] static constexpr bool any_of(F&& func) noexcept(std::conjunction_v<std::is_nothrow_invocable<F, decltype(Values)>...>)
			{
				return (std::invoke(func, Values) || ...);
			}

			template<class F>
			[[nodiscard]] static constexpr bool none_of(F&& func) noexcept(std::conjunction_v<std::is_nothrow_invocable<F, decltype(Values)>...>)
			{
				return (!std::invoke(func, Values) && ...);
			}

			template<class F>
			static constexpr void for_each(F&& func) noexcept(std::conjunction_v<std::is_nothrow_invocable<F, decltype(Values)>...>)
			{
				(std::invoke(func, Values), ...);
			}

			template<auto... Values2>
			using append = value_list<Values..., Values2...>;
		private:
			template<typename...>
			struct concatenate_helper : std::type_identity<value_list> {};

			template<auto... Types2, template<auto...> typename ValueList1, typename... ValueListN>
			struct concatenate_helper<ValueList1<Types2...>, ValueListN...> : std::type_identity<
				typename value_list::template append<Types2...>::concatenate_helper<ValueListN...>::type
			> {};
		public:
			template<typename... ValueList>
			using concatenate = typename concatenate_helper<ValueList...>::type;
		private:
			template<template<auto> class Predicate, auto...>
			struct filter_helper : std::type_identity<value_list<>> {};

			template<template<auto> class Predicate, auto Value1, auto... ValueN>
			struct filter_helper<Predicate, Value1, ValueN...> : std::type_identity<
				std::conditional_t<Predicate<Value1>::value,
					typename value_list<Value1>::template concatenate<typename filter_helper<Predicate, ValueN...>::type>,
					typename filter_helper<Predicate, ValueN...>::type
				>
			> {};

			template<index_type Offset, class Count>
			struct sub_list_helper;

			template<index_type Offset, std::size_t... I>
			struct sub_list_helper<Offset, std::index_sequence<I...>> : std::type_identity<value_list<get<I + Offset>()...>> {};

			template<template<auto> class Function, auto... Values2>
			using transform_to_types_helper = type_list<typename Function<Values2>::type...>;
		public:
			template<template<auto> class Predicate>
			using filter = typename filter_helper<Predicate, Values...>::type;

			template<template<auto> class Function>
			using transform = value_list<Function<Values>::value...>;

			// helper needed because MSVC cannot do this properly:
			// type_list<typename Function<Values>::type...>
			// So when I delay it to a helper, MSVC is fine with that.
			template<template<auto> class Function>
			using transform_to_types = transform_to_types_helper<Function, Values...>;

			template<index_type Offset, index_type Count = npos>
				requires(Offset < size())
			using sub_list = typename sub_list_helper<Offset, std::make_index_sequence<std::min(size() - Offset, Count)>>::type;
	};

	export
	template<template<auto> class Function, auto... Values>
	using transform_values = typename value_list<Values...>::template transform<Function>;

	export
	template<template<auto> class Predicate, auto... Values>
	using filter_values = typename value_list<Values...>::template filter<Predicate>;

	export
	template<typename... ValueLists>
	using concatenate_values = typename value_list<>::template concatenate<ValueLists...>;

	template<auto CurrentValue, auto Finish, class Operation>
	struct iota_impl : std::type_identity<
		concatenate_values<value_list<CurrentValue>,
						   typename iota_impl<Operation{}(CurrentValue, 1), Finish, Operation>::type>
	> {};

	template<auto CurrentValue, auto Finish, class Operation>
		requires(CurrentValue == Finish)
	struct iota_impl<CurrentValue, Finish, Operation> : std::type_identity<value_list<>> {};

	export
	template<auto Start, auto Finish>
		requires(std::integral<decltype(Start)> &&
				 std::integral<decltype(Finish)> &&
				 std::same_as<decltype(Start), decltype(Finish)>)
	using iota = typename iota_impl<Start, Finish, std::conditional_t<Start <= Finish, std::plus<>, std::minus<>>>::type;

	export
	template<std::size_t... Ints>
	using index_sequence = value_list<Ints...>;

	export
	template<class T, T N>
	using make_integer_sequence = iota<static_cast<T>(0), N>;

	export
	template<std::size_t N>
	using make_index_sequence = make_integer_sequence<std::size_t, N>;

	export
	template<class... T>
	using index_sequence_for = make_index_sequence<sizeof...(T)>;

	export
	template<std::size_t N, auto V>
	struct gen_value_list
	{
		using type = value_list<V>::template concatenate<gen_value_list<N - 1, V>::type>;
	};

	export
	template<auto V>
	struct gen_value_list<0, V> : std::type_identity<value_list<>> {};

	export
	template<std::size_t N, auto V>
	using gen_value_list_t = typename gen_value_list<N, V>::type;
}