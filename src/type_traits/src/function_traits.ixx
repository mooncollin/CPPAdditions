export module cmoon.type_traits:function_traits;

import std.core;

namespace cmoon
{   
    export
    template<typename F>
    struct function_traits;

    export
    template<typename Return, typename... Args> // Free Function
    struct function_traits<Return(Args...)>
    {
        using result_type = Return;
        using decay_type  = Return(*)(Args...);
        using arguments   = std::tuple<Args...>;

        template<std::size_t I>
        using argument = std::tuple_element_t<I, arguments>;

        static constexpr auto arity {sizeof...(Args)};
    };

    export
    template<typename Return, typename... Args> // Function Pointers
    struct function_traits<Return(*)(Args...)> : function_traits<Return(Args...)> {};

    export
    template<typename Class, class Return, typename... Args> // Member Functions
    struct function_traits<Return(Class::*)(Args...)> : function_traits<Return(Args...)>
    {
        using class_type = Class;
    };

    export
    template<typename Class, class Return, typename... Args> // const member functions and lambdas
    struct function_traits<Return(Class::*)(Args...) const> : function_traits<Return(Class::*)(Args...)> {};
}