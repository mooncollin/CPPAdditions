export module cmoon.html.make_attributes;

import std.core;

import cmoon.html.no_attributes;
import cmoon.html.static_attributes;

namespace cmoon::html
{
    export
    template<class... Attributes>
    constexpr auto make_attributes(Attributes&&... attributes)
    {
        if constexpr (sizeof...(Attributes) == 0)
        {
            return no_attributes;
        }
        else
        {
            return static_attributes{std::forward<Attributes>(attributes)...};
        }
    }
}