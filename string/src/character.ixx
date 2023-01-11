export module cmoon.string.character;

import std.core;

namespace cmoon
{
	export
    int hex_to_base10(int ch) noexcept
    {
        const auto uppered = std::toupper(ch);
        return uppered >= 'A' ? uppered - 'A' + 10 : uppered - '0';
    }
}