export module cmoon.meta:type_list;

import std.core;

import cmoon.type_traits;

namespace cmoon::meta
{
	export
	template<typename... Types>
	struct type_list
	{
		template<typename... Types2>
		friend struct type_list;

		public:
			using index_type = std::size_t;
			using tuple_t = std::tuple<Types...>;

			static constexpr index_type npos {std::numeric_limits<index_type>::max()};

			[[nodiscard]] static constexpr index_type size() noexcept
			{
				return sizeof...(Types);
			}

			[[nodiscard]] static constexpr bool empty() noexcept
			{
				return size() == 0;
			}

			template<index_type N>
				requires(N < size())
			using type = std::tuple_element_t<N, tuple_t>;
			
			#pragma warning(push)
			#pragma warning(disable : 4305)
			template<typename T>
			[[nodiscard]] static constexpr index_type index() noexcept
			{
				return []<auto... Ns>(std::index_sequence<Ns...>)
				{
					using i = std::disjunction<
						std::integral_constant<std::size_t, (1 + Ns) * std::same_as<T, Types>>...
					>;

					if constexpr (i::value != 0)
					{
						return i::value - 1;
					}
					else
					{
						return npos;
					}
				}(std::make_index_sequence<size()>{});
			}
			#pragma warning(pop)

			template<typename T>
			[[nodiscard]] static constexpr bool contains() noexcept
			{
				return std::disjunction_v<std::is_same<T, Types>...>;
			}

			template<template<typename> class Predicate>
			[[nodiscard]] static constexpr bool all_of() noexcept
			{
				return std::conjunction_v<Predicate<Types>...>;
			}

			template<template<typename> class Predicate>
			[[nodiscard]] static constexpr bool any_of() noexcept
			{
				return std::disjunction_v<Predicate<Types>...>;
			}

			template<template<typename> class Predicate>
			[[nodiscard]] static constexpr bool none_of() noexcept
			{
				return std::conjunction_v<std::negation<Predicate<Types>>...>;
			}

			template<template<typename> typename Function, typename... Args>
			static constexpr void for_each(Args&&... args) noexcept(std::conjunction_v<std::is_nothrow_invocable<Function<Types>>...> &&
													  				std::conjunction_v<std::is_nothrow_default_constructible<Function<Types>>...>)
			{
				(std::invoke(Function<Types>{}, args...), ...);
			}

			template<typename... Types2>
			using append = type_list<Types..., Types2...>;
		private:
			template<typename...>
			struct concatenate_helper : std::type_identity<type_list> {};

			template<typename... Types2, template<typename...> typename TypeList1, typename... TypeListN>
			struct concatenate_helper<TypeList1<Types2...>, TypeListN...> :
				type_list::template append<Types2...>::concatenate_helper<TypeListN...> {};
		public:
			template<class... TypeLists>
			using concatenate = typename concatenate_helper<TypeLists...>::type;
		private:
			template<template<typename> class Predicate, typename...>
			struct filter_helper : std::type_identity<type_list<>> {};

			template<template<typename> class Predicate, typename Type1, typename... TypeN>
			struct filter_helper<Predicate, Type1, TypeN...> :
				std::conditional<Predicate<Type1>::value,
					typename type_list<Type1>::template concatenate<typename filter_helper<Predicate, TypeN...>::type>,
					typename filter_helper<Predicate, TypeN...>::type
				> {};

			template<index_type Offset, class Count>
			struct sub_list_helper;

			template<index_type Offset, std::size_t... I>
			struct sub_list_helper<Offset, std::index_sequence<I...>> : std::type_identity<type_list<type<I + Offset>...>> {};

			template<class Out, class In>
			struct unique_helper;

			template<class... Out, class In1, class... InN>
			struct unique_helper<type_list<Out...>, type_list<In1, InN...>>
				: std::conditional<type_list<Out...>::template contains<In1>(),
					typename unique_helper<type_list<Out...>, type_list<InN...>>::type,
					typename unique_helper<type_list<Out..., In1>, type_list<InN...>>::type
				> {};

			template<class Out>
			struct unique_helper<Out, type_list<>> : std::type_identity<Out> {};

			template<class Default, template<typename> class Predicate, class...>
			struct find_helper : std::type_identity<Default> {};

			template<class Default, template<typename> class Predicate, class T1, class... TN>
			struct find_helper<Default, Predicate, T1, TN...>
				: std::conditional<Predicate<T1>::value,
					T1,
					typename find_helper<Default, Predicate, TN...>::type
				> {};
		public:
			template<template<typename> class Predicate>
			using filter = typename filter_helper<Predicate, Types...>::type;

			template<template<typename> class Function>
			using transform = type_list<typename Function<Types>::type...>;

			template<index_type Offset, index_type Count = npos>
				requires(Offset < size())
			using sub_list = typename sub_list_helper<Offset, std::make_index_sequence<std::min(size() - Offset, Count)>>::type;

			using unique = typename unique_helper<type_list<>, type_list>::type;

			[[nodiscard]] static constexpr bool is_unique() noexcept
			{
				return unique::size() == size();
			}

			[[nodiscard]] static constexpr bool is_all_same_type() noexcept
			{
				return unique::size() <= 1;
			}

			template<template<typename> class Predicate, class Default = cmoon::nonesuch>
			using find = typename find_helper<Default, Predicate, Types...>::type;

			template<template<typename...> typename T, typename... ExtraArgs>
			using complete_type = T<ExtraArgs..., Types...>;
	};

	export
	template<std::size_t Index, typename... Ts>
		requires(Index <= sizeof...(Ts))
	using get_type = typename type_list<Ts...>::template type<Index>;

	template<typename>
	struct extract_types_into_type_list_impl : std::type_identity<type_list<>> {};

	template<template<typename...> typename Tuple, typename... Types>
	struct extract_types_into_type_list_impl<Tuple<Types...>> : std::type_identity<type_list<Types...>> {};

	export
	template<class T>
	using extract_types_into_type_list = typename extract_types_into_type_list_impl<T>::type;

	export
	template<template<class> class Function, typename... Ts>
	using transform_types = typename type_list<Ts...>::template transform<Function>;

	export
	template<template<class> class Predicate, typename... Ts>
	using filter_types = typename type_list<Ts...>::template filter<Predicate>;

	export
	template<class... TypeLists>
	using concatenate_types = typename type_list<>::template concatenate<TypeLists...>;

	export
	template<typename... Ts>
	using unique_types = typename type_list<Ts...>::unique;
}
