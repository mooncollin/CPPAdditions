export module cmoon.html.element;

import std.core;

import cmoon.type_traits;

import cmoon.html.tag_concept;
import cmoon.html.no_attributes;
import cmoon.html.tag_traits;

namespace cmoon::html
{
    template<class T>
    struct unwrap_reference_keep_const : std::type_identity<std::decay_t<T>> {};

    template<class T>
    struct unwrap_reference_keep_const<std::reference_wrapper<T>> : std::type_identity<T&> {};

    template<class T>
    struct unwrap_reference_keep_const<std::reference_wrapper<const T>> : std::type_identity<const T&> {};

    template<class T>
    using unwrap_reference_keep_const_t = typename unwrap_reference_keep_const<T>::type;

    template<class T>
    struct wrap_type : std::type_identity<T> {};

    template<class T>
    struct wrap_type<T&> : std::type_identity<std::reference_wrapper<T>> {};

    template<class T>
    struct wrap_type<const T&> : std::type_identity<std::reference_wrapper<const T>> {};

    template<class T>
    using wrap_type_t = typename wrap_type<T>::type;

    template<class T>
    [[nodiscard]] constexpr T& unwrap_reference_fn(T& t) noexcept
    {
        return t;
    }

    template<class T>
    [[nodiscard]] constexpr T& unwrap_reference_fn(std::reference_wrapper<T> t) noexcept
    {
        return t.get();
    }

    template<class Tag>
    class tag_base
    {
        public:
            using tag_type = std::decay_t<Tag>;

            constexpr tag_base() = default;
            constexpr tag_base(const tag_base&) = default;
            constexpr tag_base(tag_base&&) noexcept = default;

            constexpr tag_base& operator=(const tag_base&) = default;
            constexpr tag_base& operator=(tag_base&&) noexcept = default;

            template<class Tag2>
            constexpr tag_base(Tag2&& t) noexcept
                : tag_{std::forward<Tag2>(t)} {}

            [[nodiscard]] constexpr tag_type& tag() noexcept
            {
                return unwrap_reference_fn(tag_);
            }

            [[nodiscard]] constexpr const tag_type& tag() const noexcept
            {
                return unwrap_reference_fn(tag_);
            }
        protected:
            wrap_type_t<Tag> tag_;
    };

    template<class Tag>
        requires(std::is_empty_v<Tag> &&
                 std::is_trivial_v<Tag>)
    class tag_base<Tag>
    {
        public:
            using tag_type = std::decay_t<Tag>;
            
            constexpr tag_base() noexcept = default;
            constexpr tag_base(const tag_base&) noexcept = default;
            constexpr tag_base(tag_base&&) noexcept = default;

            constexpr tag_base& operator=(const tag_base&) noexcept = default;
            constexpr tag_base& operator=(tag_base&&) noexcept = default;

            template<class Tag2>
            constexpr tag_base(Tag2&&) noexcept {}

            [[nodiscard]] constexpr tag_type tag() const noexcept
            {
                return tag_type{};
            }
    };

    template<class Attributes>
    class attributes_base
    {
        public:
            using attributes_type = std::decay_t<Attributes>;

            constexpr attributes_base() = default;
            constexpr attributes_base(const attributes_base&) = default;
            constexpr attributes_base(attributes_base&&) noexcept = default;

            constexpr attributes_base& operator=(const attributes_base&) = default;
            constexpr attributes_base& operator=(attributes_base&&) noexcept = default;

            template<class Attributes2>
            constexpr attributes_base(Attributes2&& t) noexcept
                : attributes_{std::forward<Attributes2>(t)} {}

            [[nodiscard]] constexpr attributes_type& attributes() noexcept
            {
                return unwrap_reference_fn(attributes_);
            }

            [[nodiscard]] constexpr const attributes_type& attributes() const noexcept
            {
                return unwrap_reference_fn(attributes_);
            }
        protected:
            wrap_type_t<Attributes> attributes_;
    };

    template<class Attributes>
        requires(std::is_empty_v<Attributes> &&
                 std::is_trivial_v<Attributes>)
    class attributes_base<Attributes>
    {
        public:
            using attributes_type = std::decay_t<Attributes>;

            constexpr attributes_base() noexcept = default;
            constexpr attributes_base(const attributes_base&) noexcept = default;
            constexpr attributes_base(attributes_base&&) noexcept = default;

            constexpr attributes_base& operator=(const attributes_base&) noexcept = default;
            constexpr attributes_base& operator=(attributes_base&&) noexcept = default;

            template<class Attributes2>
            constexpr attributes_base(Attributes2&&) noexcept {}

            [[nodiscard]] constexpr attributes_type attributes() const noexcept
            {
                return attributes_type{};
            }
    };

    template<class... Children>
    class children_base
    {
        public:
            constexpr children_base() = default;
            constexpr children_base(const children_base&) = default;
            constexpr children_base(children_base&&) noexcept = default;

            constexpr children_base& operator=(const children_base&) = default;
            constexpr children_base& operator=(children_base&&) noexcept = default;

            template<class... Children2>
            constexpr children_base(Children2&&... children) noexcept
                : children_{std::forward<Children2>(children)...} {}

            [[nodiscard]] constexpr std::tuple<std::unwrap_reference_t<Children>...> children() noexcept
            {
                return children_;
            }

            [[nodiscard]] constexpr std::tuple<std::unwrap_reference_t<Children>...> children() const noexcept
            {
                return children_;
            }
        protected:
            std::tuple<wrap_type_t<Children>...> children_;
    };

    template<class... Children>
        requires(sizeof...(Children) == 0 ||
                 (
                    std::conjunction_v<std::is_empty<Children>...> &&
                    std::conjunction_v<std::is_trivial<Children>...>
                 ))
    class children_base<Children...>
    {
        public:
            constexpr children_base() noexcept = default;
            constexpr children_base(const children_base&) noexcept = default;
            constexpr children_base(children_base&&) noexcept = default;

            constexpr children_base& operator=(const children_base&) noexcept = default;
            constexpr children_base& operator=(children_base&&) noexcept = default;

            template<class... Children2>
            constexpr children_base(Children2&&...) noexcept {}

            [[nodiscard]] constexpr std::tuple<std::decay_t<Children>...> children() const noexcept
            {
                return {};
            }
    };

    export
    template<tag_concept Tag, typename Attributes = no_attributes_t, typename... Children>
    class element : public tag_base<Tag>, public attributes_base<Attributes>, public children_base<Children...>
    {
        public:
            constexpr element() = default;

            constexpr element(const element&) = default;
            constexpr element(element&&) noexcept = default;

            constexpr element& operator=(const element&) = default;
            constexpr element& operator=(element&&) noexcept = default;

            template<class Tag2, class Attributes2, class... Children2>
            constexpr element(Tag2&& t = {}, Attributes2&& a = {}, Children2&&... children) noexcept
                : tag_base<Tag>{std::forward<Tag2>(t)},
                  attributes_base<Attributes>{std::forward<Attributes2>(a)},
                  children_base<Children...>{std::forward<Children2>(children)...} {}
    };

    // For some strange reason, the attributes_base still adds a one byte size even
    // if it's empty. So this specialization makes sure the size is one, instead of two
    // on an empty tag object.
    export
    template<tag_concept Tag>
    class element<Tag, no_attributes_t> : public tag_base<Tag>, public children_base<>
    {
        public:
            using attributes_type = no_attributes_t;

            constexpr element() = default;

            constexpr element(const element&) = default;
            constexpr element(element&&) noexcept = default;

            constexpr element& operator=(const element&) = default;
            constexpr element& operator=(element&&) noexcept = default;

            template<class Tag2>
                requires(!std::same_as<std::decay_t<Tag2>, element>)
            constexpr element(Tag2&& t, cmoon::html::no_attributes_t = {}) noexcept
                : tag_base<Tag>{std::forward<Tag2>(t)} {}

            [[nodiscard]] constexpr attributes_type attributes() const noexcept
            {
                return no_attributes;
            }
    };

    export
    template<tag_concept Tag, typename Attributes = no_attributes_t, typename... Children>
    element(Tag&&, Attributes&&, Children&&...) -> element<unwrap_reference_keep_const_t<Tag>, unwrap_reference_keep_const_t<Attributes>, unwrap_reference_keep_const_t<Children>...>;

    export
    template<tag_concept Tag>
    element(Tag&&) -> element<unwrap_reference_keep_const_t<Tag>, no_attributes_t>;

    struct indentation_t
    {
        static int xalloc_idx;
        static int force_xalloc_idx;

        int num_spaces;
    };

    export
    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const indentation_t& pp)
    {
        os.iword(indentation_t::xalloc_idx) = pp.num_spaces;
        return os;
    }

    int indentation_t::xalloc_idx       = std::ios_base::xalloc();
    int indentation_t::force_xalloc_idx = std::ios_base::xalloc();

    export
    constexpr indentation_t indentation(int spaces) noexcept
    {
        return {spaces};
    }

    export
    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>& no_indentation(std::basic_ostream<CharT, Traits>& os)
    {
        os.iword(indentation_t::xalloc_idx) = 0;
        return os;
    }

    export
    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>& force_indentation(std::basic_ostream<CharT, Traits>& os)
    {
        os.iword(indentation_t::force_xalloc_idx) = 1;
        return os;
    }

    export
    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>& print_indentation(std::basic_ostream<CharT, Traits>& os)
    {
        const auto spaces {os.iword(indentation_t::xalloc_idx)};

        for (int i {0}; i < spaces; ++i)
        {
            std::cout << ' ';
        }

        return os;
    }

    template<class CharT, class Traits, class T>
    void print_helper(std::basic_ostream<CharT, Traits>& os, const T& other, bool, const int, const int indentation)
    {
        for (int i {0}; i < indentation; ++i)
        {
            os << ' ';
        }

        os << other;
    }

    template<class CharT, class Traits, class Tag, class Attributes, class... Children>
    void print_helper(std::basic_ostream<CharT, Traits>& os, const element<Tag, Attributes, Children...>& e, const bool first, [[maybe_unused]] const int indentation_increment, const int indentation)
    {
        using t_traits = tag_traits<Tag>;
        if (!first)
        {
            for (int i {0}; i < indentation; ++i)
            {
                os << ' ';
            }
        }

        if constexpr (!t_traits::is_end_tag())
        {
            os << '<';
            os << e.tag().name();
            if constexpr (!std::same_as<std::decay_t<Attributes>, no_attributes_t>)
            {
                os << ' ';
                os << e.attributes();
            }
            os << '>';
            if constexpr (sizeof...(Children) > 0)
            {
                if (indentation > 0)
                {
                    os << '\n';
                }
                std::apply([&](const auto&... child) {
                    (print_helper(os, child, false, indentation_increment, indentation + indentation_increment * !first), ...);
                }, e.children());
                if constexpr (std::disjunction_v<cmoon::is_specialization<Children, element>...>)
                {
                    if (!first)
                    {
                        for (int i {0}; i < indentation; ++i)
                        {
                            os << ' ';
                        }
                    }
                }
            }
        }
        if (!e.tag().is_self_closing())
        {
            os << "</";
            os << e.tag().name();
            os << '>';
        }
        if constexpr (!t_traits::is_start_tag())
        {
            if (indentation > 0)
            {
                os << '\n';
            }
        }
    }

    export
    template<class Tag, class Attributes, class... Children>
    std::ostream& operator<<(std::ostream& os, const element<Tag, Attributes, Children...>& e)
    {
        const auto indentation {os.iword(indentation_t::xalloc_idx)};
        const auto force_indentation {os.iword(indentation_t::force_xalloc_idx)};
        print_helper(os, e, !force_indentation, indentation, indentation);
        os.iword(indentation_t::force_xalloc_idx) = 0;
        return os;
    }
}