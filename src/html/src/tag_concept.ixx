export module cmoon.html.tag_concept;

import std.core;

namespace cmoon::html
{
    export
    template<class T>
    concept tag_concept =
        requires(const T& t)
    {
        { t.is_self_closing() } noexcept -> std::same_as<bool>;
        
        // MSVC cannot compile this:
        // { t.name() }            noexcept -> std::convertible_to<std::string_view>;
        { t.name() }            noexcept;
    };
}