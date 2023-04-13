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
}