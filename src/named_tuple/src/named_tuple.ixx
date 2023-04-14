export module cmoon.named_tuple;

import std.core;

import cmoon.meta;
import cmoon.concepts;

namespace cmoon
{
    export
    struct no_ordering_t {};

    export
    constexpr no_ordering_t no_ordering;

    export
    template<typename... Ts>
    class named_tuple
    {
        private:
            template<class Tuple>
            static constexpr std::tuple<Ts...> no_ordering_helper(Tuple&& t)
            {
                // Incoming Tuple holds same types as Ts..., but may be forwarded.
                // We need to grab the next Ts in Tuple, but also forward that same value
                // to capture moves.
                using regular_types = cmoon::meta::extract_types_into_type_list<std::decay_t<Tuple>>;
                using decayed_types = typename regular_types::template transform<std::decay>;
                return {
                    std::forward<typename regular_types::template type<decayed_types::template index<Ts>()>>(
                        std::get<decayed_types::template index<Ts>()>(t)
                    )...
                };
            }
        public:
            using types = cmoon::meta::type_list<Ts...>;
            static_assert(types::is_unique(),
                          "Types in named_tuple must be unique");

            constexpr named_tuple() noexcept(std::conjunction_v<std::is_nothrow_default_constructible<Ts>...>) = default;
            constexpr named_tuple(const named_tuple&) = default;
            constexpr named_tuple(named_tuple&&) noexcept = default;
            constexpr named_tuple& operator=(const named_tuple&) = default;
            constexpr named_tuple& operator=(named_tuple&&) noexcept = default;

            template<class... Ts2>
                requires(sizeof...(Ts2) <= sizeof...(Ts) &&
                         std::conjunction_v<std::is_convertible<Ts2, Ts>...>)
            constexpr named_tuple(Ts2&&... ts) noexcept(std::conjunction_v<std::is_nothrow_convertible<Ts2, Ts>...>)
                : values_{std::forward<Ts2>(ts)...} {}

            template<cmoon::specialization_of<std::tuple> Tuple>
            constexpr named_tuple(Tuple&& t)
                : values_{std::forward<Tuple>(t)} {}

            template<cmoon::specialization_of<std::tuple> Tuple>
            constexpr named_tuple(no_ordering_t, Tuple&& t)
                : values_{no_ordering_helper(std::forward<Tuple>(t))} {}

            template<class... Ts2>
                requires(sizeof...(Ts2) <= sizeof...(Ts))
            constexpr named_tuple(no_ordering_t, Ts2&&... ts)
                : named_tuple{no_ordering, std::forward_as_tuple(std::forward<Ts2>(ts)...)} {}

            template<typename T>
            [[nodiscard]] constexpr T& get() & noexcept
            {
                return std::get<T>(values_);
            }

            template<typename T>
            [[nodiscard]] constexpr T&& get() && noexcept
            {
                return std::move(std::get<T>(values_));
            }

            template<typename T>
            [[nodiscard]] constexpr const T& get() const& noexcept
            {
                return std::get<T>(values_);
            }

            template<typename T>
            [[nodiscard]] static constexpr bool has_attr() noexcept
            {
                return types::template contains<T>();
            }

            [[nodiscard]] constexpr std::tuple<Ts...>& values() & noexcept
            {
                return values_;
            }

            [[nodiscard]] constexpr std::tuple<Ts...>&& values() && noexcept
            {
                return std::move(values_);
            }

            [[nodiscard]] constexpr const std::tuple<Ts...>& values() const& noexcept
            {
                return values_;
            }
        private:
            template<class TL>
            struct combine_helper;

            template<typename... Ts2>
            struct combine_helper<cmoon::meta::type_list<Ts2...>>
            {
                using type = named_tuple<Ts2...>;

                template<class T, class NT, class... NTs>
                [[nodiscard]] static constexpr decltype(auto) pick_tuple(NT&& nt, NTs&&... nts)
                {
                    if constexpr (std::decay_t<NT>::template has_attr<T>())
                    {
                        return std::forward<NT>(nt).template get<T>();
                    }
                    else
                    {
                        return pick_tuple<T>(std::forward<NTs>(nts)...);
                    }
                }

                template<class... NTs>
                static constexpr type combine(NTs&&... nts)
                {
                    return {
                        pick_tuple<Ts2>(std::forward<NTs>(nts)...)...
                    };
                }
            };
        public:
            template<class... NT>
            auto combine(NT&&... nts) const&
            {
                using ts = typename types::template concatenate<typename std::decay_t<NT>::types...>::unique;
                return combine_helper<ts>::combine(*this, std::forward<NT>(nts)...);
            }

            template<class... NT>
            using combine_t = decltype(combine(std::declval<NT>()...));
        private:
            [[no_unique_address]] std::tuple<Ts...> values_;
    };

    export
    template<typename... Ts>
    named_tuple(Ts&&...) -> named_tuple<std::decay_t<Ts>...>;
}

namespace std
{
    export
    template<typename T, typename... Ts>
    [[nodiscard]] constexpr T& get(cmoon::named_tuple<Ts...>& a) noexcept
    {
        return a.template get<T>();
    }

    export
    template<typename T, typename... Ts>
    [[nodiscard]] constexpr const T& get(const cmoon::named_tuple<Ts...>& a) noexcept
    {
        return a.template get<T>();
    }
}