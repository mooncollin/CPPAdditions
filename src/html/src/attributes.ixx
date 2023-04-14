export module cmoon.html.attributes;

import std.core;

namespace cmoon::html
{
    template<auto V>
    struct nontype_template {};

    template<class T>
    struct allowed_nontype_template : std::false_type {};

    template<class T>
        requires(requires { typename nontype_template<T{}>; })
    struct allowed_nontype_template<T> : std::true_type {};

    template<class CRTP, class T>
    struct base_base_attribute
    {
        friend std::ostream& operator<<(std::ostream& os, const base_base_attribute& a)
        {
            const auto derived {static_cast<const CRTP&>(a)};
            os << derived.get_name();
            os << "=\"";
            os << a.value;
            os << '"';
            return os;
        }

        T value;
    };

    export
    template<class CRTP, class T, class CT = T>
    struct base_attribute : public base_base_attribute<CRTP, T>
    {
        struct constant
        {
            using parent_type = CRTP;

            friend std::ostream& operator<<(std::ostream& os, const constant& a)
            {
                os << CRTP::get_name();
                os << "=\"";
                os << a.value;
                os << '"';
                return os;
            }

            CT value;
        };
    };

    export
    template<class CRTP, class T, class CT>
        requires(allowed_nontype_template<T>::value)
    struct base_attribute<CRTP, T, CT> : public base_base_attribute<CRTP, T>
    {
        template<CT V>
        struct constant
        {
            using parent_type = CRTP;
            
            friend std::ostream& operator<<(std::ostream& os, const constant&)
            {
                os << CRTP::get_name();
                os << "=\"";
                os << V;
                os << '"';
                return os;
            }

            static constexpr CT value {V};
        };
    };

    export
    template<class CRTP, class T>
    struct base_attribute<CRTP, T, void> : public base_base_attribute<CRTP, T> {};

    export
    template<class CRTP>
    struct base_attribute<CRTP, void, void>
    {
        friend std::ostream& operator<<(std::ostream& os, const base_attribute& a)
        {
            const auto derived {static_cast<const CRTP&>(a)};
            os << derived.get_name();
            return os;
        }
    };

    export
    class custom_attribute : public base_attribute<custom_attribute, std::string, void>
    {
        public:
            constexpr custom_attribute(std::string name, std::string value)
                : base_attribute<custom_attribute, std::string, void>{value},
                  name_{name} {}

            [[nodiscard]] constexpr const std::string& get_name() const noexcept
            {
                return name_;
            }

            class constant : public base_attribute<constant, std::string_view, void>
            {
                public:
                    using parent_type = custom_attribute;

                    constexpr constant(std::string_view name, std::string_view value) noexcept
                        : base_attribute<constant, std::string_view, void>{value},
                          name_{name} {}

                    [[nodiscard]] constexpr std::string_view get_name() const noexcept
                    {
                        return name_;
                    }
                private:
                    std::string_view name_;
            };
        private:
            std::string name_;
    };

    export
    namespace attributes
    {
        export
        struct accesskey : public base_attribute<accesskey, char>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "accesskey";
            }
        };

        export
        struct async : public base_attribute<async, void>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "async";
            }
        };

        export
        struct lang : public base_attribute<lang, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "lang";
            }
        };

        export
        struct charset : public base_attribute<charset, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "charset";
            }
        };

        export
        struct name : public base_attribute<name, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "name";
            }
        };

        export
        struct content : public base_attribute<content, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "content";
            }
        };

        export
        struct rel : public base_attribute<rel, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "rel";
            }
        };

        export
        struct href : public base_attribute<href, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view get_name() noexcept
            {
                return "href";
            }
        };
    }
}