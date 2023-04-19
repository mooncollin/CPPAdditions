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
            os << derived.name();
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
                os << CRTP::name();
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
                os << CRTP::name();
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
            os << derived.name();
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

            [[nodiscard]] constexpr const std::string& name() const noexcept
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

                    [[nodiscard]] constexpr std::string_view name() const noexcept
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
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "accesskey";
            }
        };

        export
        struct action : public base_attribute<action, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "action";
            }
        };

        export
        struct aria_controls : public base_attribute<aria_controls, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "aria-controls";
            }
        };

        export
        struct aria_expanded : public base_attribute<aria_expanded, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "aria-expanded";
            }
        };

        export
        struct aria_label : public base_attribute<aria_label, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "aria-label";
            }
        };

        export
        struct async : public base_attribute<async, void>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "async";
            }
        };

        export
        struct charset : public base_attribute<charset, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "charset";
            }
        };

        export
        struct class_ : public base_attribute<class_, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "class";
            }
        };

        export
        struct content : public base_attribute<content, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "content";
            }
        };

        export
        struct data_bs_target : public base_attribute<data_bs_target, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "data-bs-target";
            }
        };

        export
        struct data_bs_toggle : public base_attribute<data_bs_toggle, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "data-bs-toggle";
            }
        };

        export
        struct d : public base_attribute<d, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "d";
            }
        };

        export
        struct height : public base_attribute<height, int>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "height";
            }
        };

        export
        struct href : public base_attribute<href, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "href";
            }
        };

        export
        struct id : public base_attribute<id, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "id";
            }
        };

        export
        struct lang : public base_attribute<lang, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "lang";
            }
        };

        export
        struct method : public base_attribute<method, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "method";
            }
        };

        export
        struct name_ : public base_attribute<name_, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "name";
            }
        };

        export
        struct placeholder : public base_attribute<placeholder, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "placeholder";
            }
        };

        export
        struct rel : public base_attribute<rel, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "rel";
            }
        };

        export
        struct required : public base_attribute<required, void>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "required";
            }
        };

        export
        struct type : public base_attribute<type, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "type";
            }
        };

        export
        struct value : public base_attribute<value, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "value";
            }
        };

        export
        struct viewbox : public base_attribute<viewbox, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "viewBox";
            }
        };

        export
        struct width : public base_attribute<width, int>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "width";
            }
        };

        export
        struct xmlns : public base_attribute<xmlns, std::string, std::string_view>
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return "xmlns";
            }
        };
    }
}