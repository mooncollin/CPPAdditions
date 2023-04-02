import std.core;

import cmoon.fixed_valarray;
import cmoon.meta;

// template<typename T, std::size_t S>
// void print_valarray(const cmoon::fixed_valarray<T, S>& v)
// {
//     for (const auto& value : v)
//     {
//         std::cout << value << ' ';
//     }
//     std::cout << '\n';
// }

template<typename T, std::size_t S>
void print_valarray2(const cmoon::fixed_valarray<T, S>& v)
{
    for (std::size_t i {0}; i < v.size(); ++i)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

int main()
{
    // cmoon::fixed_valarray v{10, 45, 98, 20.0f};
    cmoon::fixed_valarray v{10, 45, 98, 20.0f, 0, 0, 0, 4, 3.4f};
    // cmoon::fixed_valarray<float, 4> v;
    std::cout << typeid(decltype(v)::underlying).name() << '\n';
    print_valarray2(v);
    // auto v2 {-v};
    // cmoon::fixed_valarray<int, 1> v3{v2};
    // std::cout << v3[0] << '\n';
    // auto v2 {v + v};
    // cmoon::fixed_valarray<int, 1> v3{v2};
    // std::cout << v3[0] << '\n';
    // cmoon::fixed_valarray v {.1, .3, .6, .9};
    // cmoon::fixed_valarray<float, 5> v2{.1f, .2f, .3f};

    // std::cout << typeid(decltype(v2)::underlying).name() << '\n';
    // auto v3 = v2 + v2 + v2 + v2 + v2 + v2 + v2 + v2;
    // cmoon::fixed_valarray v4{v3};
    // std::cout << "underlying size: " << v4.underlying_size() << '\n';
    // std::cout << "size: " << v4.size() << '\n';

    // print_valarray(v);
    // print_valarray2(v2);
    // print_valarray2(v4);
}