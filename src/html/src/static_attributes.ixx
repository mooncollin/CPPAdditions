export module cmoon.html.static_attributes;

import std.core;

import cmoon.meta;
import cmoon.named_tuple;

namespace cmoon::html
{
    template<class T>
    struct to_parent : std::type_identity<T> {};

    template<class T>
        requires(requires{ typename T::parent_type; })
    struct to_parent<T> : std::type_identity<typename T::parent_type> {};

    template<class T>
    using to_parent_t = typename to_parent<T>::type;

    // Only because MSVC fails to compile pulling out the first
    // arg in the lambda use of std::apply.
    template<class T, class... Ts>
    void print_helper(std::ostream& os, const T& v, const Ts&... vs)
    {
        os << v;
        ((os << ' ' << vs), ...);
    }

    export
    template<typename... Attributes>
    class static_attributes
    {
        using nt = cmoon::named_tuple<Attributes...>;
        using types = typename nt::types;
        static_assert(types::template transform<to_parent>::is_unique(),
                      "Attributes must be unique");

        public:
            template<class... Attributes2>
            constexpr static_attributes(Attributes2... attrs) noexcept
                : attributes_{cmoon::no_ordering, std::move(attrs)...} {}

            template<typename T>
            [[nodiscard]] constexpr decltype(auto) get() noexcept
            {
                if constexpr (attributes_.template has_attr<T>())
                {
                    return std::get<T>(attributes_);
                }
                else
                {
                    using parent_types = types::template transform<to_parent>;
                    return std::get<parent_types::template index<T>()>(attributes_.values());
                }
            }

            template<typename T>
            [[nodiscard]] constexpr decltype(auto) get() const noexcept
            {
                if constexpr (types::template contains<T>())
                {
                    return std::get<T>(attributes_);
                }
                else
                {
                    using parent_types = types::template transform<to_parent>;
                    return std::get<parent_types::template index<T>()>(attributes_.values());
                }
            }

            friend std::ostream& operator<<(std::ostream& os, const static_attributes& a)
            {
                std::apply(
                    [&](const auto&... attrs) {
                        print_helper(os, attrs...);
                    }
                , a.attributes_.values());

                return os;
            }
        private:
            [[no_unique_address]] nt attributes_;
    };

    export
    template<typename... Attributes>
    static_attributes(Attributes...) -> static_attributes<std::decay_t<Attributes>...>;
}

namespace std
{
    export
    template<typename T, typename... Attributes>
    [[nodiscard]] constexpr decltype(auto) get(cmoon::html::static_attributes<Attributes...>& a) noexcept
    {
        return a.template get<T>();
    }

    export
    template<typename T, typename... Attributes>
    [[nodiscard]] constexpr decltype(auto) get(const cmoon::html::static_attributes<Attributes...>& a) noexcept
    {
        return a.template get<T>();
    }
}