export module cmoon.html.tags;

import std.core;

import cmoon.html.no_attributes;
import cmoon.html.element;

namespace cmoon::html
{
    export
    template<class T>
    struct base_tag
    {
        template<class Attributes = no_attributes_t, class... Children>
        constexpr auto operator()(Attributes&& attributes = {}, Children&&... children) const
        {
            return element{T{}, std::forward<Attributes>(attributes), std::forward<Children>(children)...};
        }
    };

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
}