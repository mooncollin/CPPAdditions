export module cmoon.html:no_attributes;

import std.core;

namespace cmoon::html
{
    export
    struct no_attributes_t {};

    export
    constexpr no_attributes_t no_attributes {};

    export
    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const no_attributes_t&)
    {
        return os;
    }
}