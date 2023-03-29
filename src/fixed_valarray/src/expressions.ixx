export module cmoon.fixed_valarray.expressions;

import std.core;

import cmoon.meta;
import cmoon.type_traits;

namespace cmoon
{
    export
    struct base_expression {};

    template<class E>
    [[nodiscard]] static constexpr decltype(auto) unwrap(const E& e, [[maybe_unused]] std::size_t i)
    {
        if constexpr (std::derived_from<E, base_expression>)
        {
            return e.underlying_index(i);
        }
        else
        {
            return e;
        }
    }

    template<class E>
    struct get_base_type : std::type_identity<cmoon::nonesuch> {};

    template<class E>
    struct has_base_type : std::bool_constant<std::derived_from<E, base_expression>> {};

    template<std::derived_from<base_expression> E>
        requires(!requires { typename E::base_type; })
    struct get_base_type<E> : std::type_identity<E> {};

    template<std::derived_from<base_expression> E>
        requires(requires { typename E::base_type; })
    struct get_base_type<E> : std::type_identity<typename E::base_type> {};

    template<class E>
    using get_base_type_t = typename get_base_type<E>::type;

    template<class... E>
    using get_ref_type_t = std::conditional_t<
        (sizeof...(E) > 1),
        std::tuple<E...>,
        std::tuple_element_t<0, std::tuple<E...>>
    >;

    template<typename OverrideValue, typename ValueType>
    struct get_value_type : std::type_identity<OverrideValue> {};

    template<typename ValueType>
    struct get_value_type<void, ValueType> : std::type_identity<ValueType> {};

    export
    template<typename OverrideValue, typename CRTP, typename... E>
    struct basic_expression : base_expression
    {
        using base_type = get_base_type_t<typename cmoon::meta::type_list<E...>::template find<has_base_type>>;
        using override_base_type = typename base_type::template rebind<
            typename get_value_type<OverrideValue, typename base_type::value_type>::type>;
        using ref_type  = get_ref_type_t<
                            std::conditional_t<
                                cmoon::is_specialization_v<E, cmoon::basic_expression>,
                                E,
                                std::conditional_t<
                                    std::derived_from<E, base_expression>,    
                                    const E&,
                                    E
                                >
                            >...
                           >;
        using value_type = typename override_base_type::value_type;

        constexpr basic_expression(const E&... refs) noexcept
            : refs{refs...} {}

        [[nodiscard]] constexpr operator override_base_type() const
        {
            return [this]<std::size_t... I>(std::index_sequence<I...>) {
                return override_base_type{static_cast<const CRTP&>(*this).underlying_index(I)...};
            }(std::make_index_sequence<override_base_type::underlying_size()>{});
        }
        
        ref_type refs;
    };

    export
    template<typename E>
    struct negate_expression : public basic_expression<void, negate_expression<E>, E>
    {
        using basic_expression<void, negate_expression<E>, E>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return -(this->refs.underlying_index(i));
        }
    };

    export
    template<typename E>
    struct positive_expression : public basic_expression<void, positive_expression<E>, E>
    {
        using basic_expression<void, positive_expression<E>, E>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return +(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    negate_expression<E> operator-(const E& e)
    {
        return {e};
    }

    export
    template<std::derived_from<base_expression> E>
    positive_expression<E> operator+(const E& e)
    {
        return {e};
    }

    export
    template<typename... Es>
    struct plus_expression : public basic_expression<void, plus_expression<Es...>, Es...>
    {
        using basic_expression<void, plus_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) + ...);
            }, this->refs);
        }

        template<class E>
        constexpr plus_expression<Es..., E> operator+(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return plus_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr plus_expression<Es..., Es2...> operator+(const plus_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return plus_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr plus_expression<E, Es...> operator+(const E& lhs, const plus_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return plus_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr plus_expression<E1, E2> operator+(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct minus_expression : public basic_expression<void, minus_expression<Es...>, Es...>
    {
        using basic_expression<void, minus_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) - ...);
            }, this->refs);
        }

        template<class E>
        constexpr minus_expression<Es..., E> operator-(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return minus_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr minus_expression<Es..., Es2...> operator-(const minus_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return minus_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr minus_expression<E, Es...> operator-(const E& lhs, const minus_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return minus_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr minus_expression<E1, E2> operator-(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct multiplies_expression : public basic_expression<void, multiplies_expression<Es...>, Es...>
    {
        using basic_expression<void, multiplies_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) * ...);
            }, this->refs);
        }

        template<class E>
        constexpr multiplies_expression<Es..., E> operator*(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return multiplies_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr multiplies_expression<Es..., Es2...> operator*(const multiplies_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return multiplies_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr multiplies_expression<E, Es...> operator*(const E& lhs, const multiplies_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return multiplies_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr multiplies_expression<E1, E2> operator*(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct divides_expression : public basic_expression<void, divides_expression<Es...>, Es...>
    {
        using basic_expression<void, divides_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) / ...);
            }, this->refs);
        }

        template<class E>
        constexpr divides_expression<Es..., E> operator/(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return divides_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr divides_expression<Es..., Es2...> operator/(const divides_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return divides_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr divides_expression<E, Es...> operator/(const E& lhs, const divides_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return divides_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr divides_expression<E1, E2> operator/(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct modulus_expression : public basic_expression<void, modulus_expression<Es...>, Es...>
    {
        using basic_expression<void, modulus_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) % ...);
            }, this->refs);
        }

        template<class E>
        constexpr modulus_expression<Es..., E> operator%(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return modulus_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr modulus_expression<Es..., Es2...> operator%(const modulus_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return modulus_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr modulus_expression<E, Es...> operator%(const E& lhs, const modulus_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return modulus_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr modulus_expression<E1, E2> operator%(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct bit_and_expression : public basic_expression<void, bit_and_expression<Es...>, Es...>
    {
        using basic_expression<void, bit_and_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) & ...);
            }, this->refs);
        }

        template<class E>
        constexpr bit_and_expression<Es..., E> operator&(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return bit_and_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr bit_and_expression<Es..., Es2...> operator&(const bit_and_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return bit_and_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr bit_and_expression<E, Es...> operator&(const E& lhs, const bit_and_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return bit_and_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr bit_and_expression<E1, E2> operator&(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct bit_or_expression : public basic_expression<void, bit_or_expression<Es...>, Es...>
    {
        using basic_expression<void, bit_or_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) | ...);
            }, this->refs);
        }

        template<class E>
        constexpr bit_or_expression<Es..., E> operator|(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return bit_or_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr bit_or_expression<Es..., Es2...> operator|(const bit_or_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return bit_or_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr bit_or_expression<E, Es...> operator|(const E& lhs, const bit_or_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return bit_or_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr bit_or_expression<E1, E2> operator|(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct bit_xor_expression : public basic_expression<void, bit_xor_expression<Es...>, Es...>
    {
        using basic_expression<void, bit_xor_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) ^ ...);
            }, this->refs);
        }

        template<class E>
        constexpr bit_xor_expression<Es..., E> operator^(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return bit_xor_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr bit_xor_expression<Es..., Es2...> operator^(const bit_xor_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return bit_xor_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr bit_xor_expression<E, Es...> operator^(const E& lhs, const bit_xor_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return bit_xor_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr bit_xor_expression<E1, E2> operator^(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct left_shift_expression : public basic_expression<void, left_shift_expression<Es...>, Es...>
    {
        using basic_expression<void, left_shift_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) << ...);
            }, this->refs);
        }

        template<class E>
        constexpr left_shift_expression<Es..., E> operator<<(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return left_shift_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr left_shift_expression<Es..., Es2...> operator<<(const left_shift_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return left_shift_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr left_shift_expression<E, Es...> operator<<(const E& lhs, const left_shift_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return left_shift_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr left_shift_expression<E1, E2> operator<<(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct right_shift_expression : public basic_expression<void, right_shift_expression<Es...>, Es...>
    {
        using basic_expression<void, right_shift_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) >> ...);
            }, this->refs);
        }

        template<class E>
        constexpr right_shift_expression<Es..., E> operator>>(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return right_shift_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr right_shift_expression<Es..., Es2...> operator>>(const right_shift_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return right_shift_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr right_shift_expression<E, Es...> operator>>(const E& lhs, const right_shift_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return right_shift_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr right_shift_expression<E1, E2> operator>>(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct logical_and_expression : public basic_expression<bool, logical_and_expression<Es...>, Es...>
    {
        using basic_expression<bool, logical_and_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) && ...);
            }, this->refs);
        }

        template<class E>
        constexpr logical_and_expression<Es..., E> operator&&(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return logical_and_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr logical_and_expression<Es..., Es2...> operator&&(const logical_and_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return logical_and_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr logical_and_expression<E, Es...> operator&&(const E& lhs, const logical_and_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return logical_and_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr logical_and_expression<E1, E2> operator&&(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<typename... Es>
    struct logical_or_expression : public basic_expression<bool, logical_or_expression<Es...>, Es...>
    {
        using basic_expression<bool, logical_or_expression<Es...>, Es...>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            return std::apply([&](const auto&... args) {
                return (unwrap(args, i) || ...);
            }, this->refs);
        }

        template<class E>
        constexpr logical_or_expression<Es..., E> operator||(const E& rhs)
        {
            return std::apply([&](const auto&... args) {
                return logical_or_expression<Es..., E>{
                    args...,
                    rhs
                };
            }, this->refs);
        }

        template<class... Es2>
        constexpr logical_or_expression<Es..., Es2...> operator||(const logical_or_expression<Es2...>& rhs)
        {
            return std::apply([&](const auto&... args) {
                return std::apply([&](const auto&... args2) {
                    return logical_or_expression<Es..., Es2...> {
                        args...,
                        args2...
                    };
                }, rhs.refs);
            }, this->refs);
        }

        template<class E>
        friend constexpr logical_or_expression<E, Es...> operator||(const E& lhs, const logical_or_expression& rhs)
        {
            return std::apply([&](const auto&... args) {
                return logical_or_expression<Es..., E>{
                    lhs,
                    args...
                };
            }, rhs.refs);
        }
    };

    export
    template<class E1, class E2>
        requires((std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>))
    constexpr logical_or_expression<E1, E2> operator||(const E1& lhs, const E2& rhs)
    {
        return {lhs, rhs};
    }

    export
    template<class E>
    struct shift_expression : public basic_expression<void, shift_expression<E>, E>
    {
        using base_type  = typename basic_expression<void, shift_expression<E>, E>::base_type;
        using value_type = typename basic_expression<void, shift_expression<E>, E>::value_type;
        using shift_type = std::make_signed_t<std::size_t>;

        template<class T>
        constexpr shift_expression(T&& t, shift_type count)
            : basic_expression<void, shift_expression<E>, E>{std::forward<T>(t)},
              count{count} {}

        constexpr auto underlying_index(std::size_t i) const
        {
            const auto new_i {i + count};
            if (new_i >= base_type::size())
            {
                return value_type{};
            }
            
            return this->refs.underlying_index(new_i);
        }

        shift_type count;
    };

    export
    template<class E>
    struct cshift_expression : public basic_expression<void, cshift_expression<E>, E>
    {
        using base_type  = typename basic_expression<void, cshift_expression<E>, E>::base_type;
        using value_type = typename basic_expression<void, cshift_expression<E>, E>::value_type;
        using shift_type = std::make_signed_t<std::size_t>;

        template<class T>
        constexpr cshift_expression(T&& t, shift_type count)
            : basic_expression<void, cshift_expression<E>, E>{std::forward<T>(t)},
              count{count} {}

        constexpr auto underlying_index(shift_type i) const
        {
            auto new_i {i + count};
            if (new_i < 0)
            {
                new_i += base_type::size();
            }

            new_i %= base_type::size();
            return this->refs.underlying_index(new_i);
        }

        shift_type count;
    };

    export
    template<typename E>
    struct abs_expression : public basic_expression<void, abs_expression<E>, E>
    {
        using basic_expression<void, abs_expression<E>, E>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::abs;
            return abs(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr abs_expression<E> abs(const E& v) noexcept
    {
        return {v};
    }

    export
    template<typename E>
    struct exp_expression : public basic_expression<void, exp_expression<E>, E>
    {
        using basic_expression<void, exp_expression<E>, E>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::exp;
            return exp(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr exp_expression<E> exp(const E& v) noexcept
    {
        return {v};
    }

    export
    template<typename E>
    struct log_expression : public basic_expression<void, log_expression<E>, E>
    {
        using basic_expression<void, log_expression<E>, E>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::log;
            return log(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr log_expression<E> log(const E& v) noexcept
    {
        return {v};
    }

    export
    template<typename E>
    struct log10_expression : public basic_expression<void, log10_expression<E>, E>
    {
        using basic_expression<void, log10_expression<E>, E>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::log10;
            return log10(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr log10_expression<E> log10(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1, class E2>
    struct pow_expression : public basic_expression<void, pow_expression<E1, E2>, E1, E2>
    {
        using basic_expression<void, pow_expression<E1, E2>, E1, E2>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::pow;
            return pow(
                unwrap(std::get<0>(this->refs), i),
                unwrap(std::get<1>(this->refs), i)
            );
        }
    };

    export
    template<class E1, class E2>
        requires(std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>)
    constexpr pow_expression<E1, E2> pow(const E1& lhs, const E2& rhs) noexcept
    {
        return {lhs, rhs};
    }

    export
    template<class E1>
    struct sqrt_expression : public basic_expression<void, sqrt_expression<E1>, E1>
    {
        using basic_expression<void, sqrt_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::sqrt;
            return sqrt(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr sqrt_expression<E> sqrt(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct sin_expression : public basic_expression<void, sin_expression<E1>, E1>
    {
        using basic_expression<void, sin_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::sin;
            return sin(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr sin_expression<E> sin(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct cos_expression : public basic_expression<void, cos_expression<E1>, E1>
    {
        using basic_expression<void, cos_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::cos;
            return cos(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr cos_expression<E> cos(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct tan_expression : public basic_expression<void, tan_expression<E1>, E1>
    {
        using basic_expression<void, tan_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::tan;
            return tan(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr tan_expression<E> tan(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct asin_expression : public basic_expression<void, asin_expression<E1>, E1>
    {
        using basic_expression<void, asin_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::asin;
            return asin(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr asin_expression<E> asin(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct acos_expression : public basic_expression<void, acos_expression<E1>, E1>
    {
        using basic_expression<void, acos_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::acos;
            return acos(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr acos_expression<E> acos(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct atan_expression : public basic_expression<void, atan_expression<E1>, E1>
    {
        using basic_expression<void, atan_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::atan;
            return atan(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr atan_expression<E> atan(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1, class E2>
    struct atan2_expression : public basic_expression<void, atan2_expression<E1, E2>, E1, E2>
    {
        using basic_expression<void, atan2_expression<E1, E2>, E1, E2>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::atan2;
            return atan2(
                unwrap(std::get<0>(this->refs), i),
                unwrap(std::get<1>(this->refs), i)
            );
        }
    };

    export
    template<class E1, class E2>
        requires(std::derived_from<E1, base_expression> || std::derived_from<E2, base_expression>)
    constexpr atan2_expression<E1, E2> atan2(const E1& lhs, const E2& rhs) noexcept
    {
        return {lhs, rhs};
    }

    export
    template<class E1>
    struct sinh_expression : public basic_expression<void, sinh_expression<E1>, E1>
    {
        using basic_expression<void, sinh_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::sinh;
            return sinh(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr sinh_expression<E> sinh(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct cosh_expression : public basic_expression<void, cosh_expression<E1>, E1>
    {
        using basic_expression<void, cosh_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::cosh;
            return cosh(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr cosh_expression<E> cosh(const E& v) noexcept
    {
        return {v};
    }

    export
    template<class E1>
    struct tanh_expression : public basic_expression<void, tanh_expression<E1>, E1>
    {
        using basic_expression<void, tanh_expression<E1>, E1>::basic_expression;

        constexpr decltype(auto) underlying_index(std::size_t i) const
        {
            using std::tanh;
            return tanh(this->refs.underlying_index(i));
        }
    };

    export
    template<std::derived_from<base_expression> E>
    constexpr tanh_expression<E> tanh(const E& v) noexcept
    {
        return {v};
    }
}