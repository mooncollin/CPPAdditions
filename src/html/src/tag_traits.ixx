export module cmoon.html.tag_traits;

import std.core;

import cmoon.html.start_tag;
import cmoon.html.end_tag;

namespace cmoon::html
{
    export
    template<class T>
    struct tag_traits
    {
        [[nodiscard]] static consteval bool is_start_tag() noexcept
        {
            return std::derived_from<T, start_tag>;
        }

        [[nodiscard]] static consteval bool is_end_tag() noexcept
        {
            return std::derived_from<T, end_tag>;
        }
    };
}