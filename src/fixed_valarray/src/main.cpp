import std.core;

import cmoon.fixed_valarray;
import cmoon.meta;

template<typename T, std::size_t S>
void print_valarray(const cmoon::fixed_valarray<T, S>& v)
{
    for (const auto& value : v)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main()
{
    constexpr cmoon::fixed_valarray v {.1, .3, .6, .9};

    constexpr auto v2 = atan(v);
    constexpr auto v3 = tan(v2);

    print_valarray(cmoon::fixed_valarray{v});
    print_valarray(cmoon::fixed_valarray{v2});
    print_valarray(cmoon::fixed_valarray{v3});
}