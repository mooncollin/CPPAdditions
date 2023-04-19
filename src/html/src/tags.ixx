export module cmoon.html.tags;

import std.core;

import cmoon.html.no_attributes;
import cmoon.html.element;
import cmoon.html.start_tag;
import cmoon.html.end_tag;

namespace cmoon::html
{
    export
    class custom_tag
    {
        public:
            constexpr custom_tag(std::string name_, const bool self_closing_ = false) noexcept
                : name_{std::move(name_)}, self_closing_{self_closing_} {}

            [[nodiscard]] constexpr bool is_self_closing() const noexcept
            {
                return self_closing_;
            }

            [[nodiscard]] constexpr bool& is_self_closing() noexcept
            {
                return self_closing_;
            }

            [[nodiscard]] constexpr std::string& name() noexcept
            {
                return name_;
            }

            [[nodiscard]] constexpr const std::string& name() const noexcept
            {
                return name_;
            }

            template<class Attributes = no_attributes_t, class... Children>
            constexpr auto operator()(Attributes&& attributes = {}, Children&&... children) &
            {
                return element{std::ref(*this), std::forward<Attributes>(attributes), std::forward<Children>(children)...};
            }

            template<class Attributes = no_attributes_t, class... Children>
            constexpr auto operator()(Attributes&& attributes = {}, Children&&... children) const&
            {
                return element{std::cref(*this), std::forward<Attributes>(attributes), std::forward<Children>(children)...};
            }

            template<class Attributes = no_attributes_t, class... Children>
            constexpr auto operator()(Attributes&& attributes = {}, Children&&... children) &&
            {
                return element{std::move(*this), std::forward<Attributes>(attributes), std::forward<Children>(children)...};
            }
        private:
            std::string name_;
            bool self_closing_;
    };

    export
    template<class T>
    struct base_tag
    {
        template<class Attributes = no_attributes_t, class... Children>
        constexpr auto operator()(Attributes&& attributes = {}, Children&&... children) const
        {
            return element{T{}, std::forward<Attributes>(attributes), std::forward<Children>(children)...};
        }

        struct start_t : start_tag
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return T::name();
            }
        };

        template<class Attributes = no_attributes_t, class... Children>
        constexpr auto start(Attributes&& attributes = {}, Children&&... children) const
        {
            return element{start_t{}, std::forward<Attributes>(attributes), std::forward<Children>(children)...};
        }

        struct end_t : end_tag
        {
            [[nodiscard]] static constexpr std::string_view name() noexcept
            {
                return T::name();
            }
        };

        constexpr auto end() const noexcept
        {
            return element{end_t{}};
        }
    };

    struct a_tag_t : base_tag<a_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "a";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr a_tag_t a_tag {};

    struct body_tag_t : base_tag<body_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "body";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr body_tag_t body_tag {};

    struct button_tag_t : base_tag<button_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "button";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr button_tag_t button_tag {};

    struct div_tag_t : base_tag<div_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "div";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr div_tag_t div_tag {};

    struct doctype_tag_t : base_tag<doctype_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "!DOCTYPE html";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return true;
        }
    };

    export
    constexpr doctype_tag_t doctype_tag {};

    struct form_tag_t : base_tag<form_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "form";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr form_tag_t form_tag {};

    struct head_tag_t : base_tag<head_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "head";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr head_tag_t head_tag {};

    struct html_tag_t : base_tag<html_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "html";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr html_tag_t html_tag {};

    struct input_tag_t : base_tag<input_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "input";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return true;
        }
    };

    export
    constexpr input_tag_t input_tag {};

    struct link_tag_t : base_tag<link_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "link";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return true;
        }
    };

    export
    constexpr link_tag_t link_tag {};

    struct meta_tag_t : base_tag<meta_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "meta";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return true;
        }
    };

    export
    constexpr meta_tag_t meta_tag {};

    struct nav_tag_t : base_tag<nav_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "nav";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr nav_tag_t nav_tag {};

    struct path_tag_t : base_tag<path_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "path";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return true;
        }
    };

    export
    constexpr path_tag_t path_tag {};

    struct span_tag_t : base_tag<span_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "span";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr span_tag_t span_tag {};

    struct svg_tag_t : base_tag<svg_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "svg";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr svg_tag_t svg_tag {};

    struct ul_tag_t : base_tag<ul_tag_t>
    {
        [[nodiscard]] static constexpr std::string_view name() noexcept
        {
            return "ul";
        }

        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };

    export
    constexpr ul_tag_t ul_tag {};
}