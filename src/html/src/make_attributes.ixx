export module cmoon.html:make_attributes;

import std.core;

import :no_attributes;
import :static_attributes;

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
            return cmoon::html::static_attributes{std::forward<Attributes>(attributes)...};
        }
    }
}