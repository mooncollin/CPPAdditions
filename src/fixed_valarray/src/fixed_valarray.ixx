export module cmoon.fixed_valarray;

import std.core;

import cmoon.fixed_valarray.underlying;
import cmoon.fixed_valarray.expressions;

namespace cmoon
{
    export
    template<class T, std::size_t S>
        requires(!std::derived_from<T, base_expression>)
    class fixed_valarray : public base_expression,
                           public underlying_valarray<T, S>
    {
        public:
            using value_type = underlying_valarray<T, S>::value_type;
            using underlying = underlying_valarray<T, S>::underlying;

            template<class T2>
            using rebind = fixed_valarray<T2, S>;

            constexpr fixed_valarray() = default;

            constexpr fixed_valarray(underlying data_)
                : underlying_valarray<T, S>{std::move(underlying)} {}

            template<std::convertible_to<value_type>... T2>
            constexpr fixed_valarray(T2&&... t2)
                : underlying_valarray<T, S>{{static_cast<value_type>(t2)...}} {}

            template<class E>
                requires(cmoon::is_specialization_v<E, basic_expression>)
            constexpr fixed_valarray(const E& e)
                : fixed_valarray{static_cast<fixed_valarray>(e)} {}

            constexpr fixed_valarray(const fixed_valarray&) = default;
            constexpr fixed_valarray(fixed_valarray&&) noexcept = default;

            constexpr fixed_valarray& operator=(const fixed_valarray&) = default;
            constexpr fixed_valarray& operator=(fixed_valarray&&) noexcept = default;

            constexpr const value_type& underlying_index(std::size_t i) const noexcept
            {
                return data_[i];
            }

            constexpr value_type& underlying_index(std::size_t i) noexcept
            {
                return data_[i];
            }

            [[nodiscard]] static constexpr std::size_t underlying_size() noexcept
            {
                return std::tuple_size_v<underlying>;
            }

            [[nodiscard]] static constexpr std::size_t size() noexcept
            {
                return S;
            }

            constexpr fixed_valarray& operator+=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) += rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator+=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) += rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator-=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) -= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator-=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) -= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator*=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) *= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator*=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) *= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator/=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) /= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator/=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) /= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator%=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) %= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator%=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) %= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator&=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) &= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator&=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) &= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator|=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) |= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator|=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) |= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator^=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) ^= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator^=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) ^= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator<<=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) <<= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator<<=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) <<= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator>>=(const fixed_valarray& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) >>= rhs.underlying_index(I)), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray& operator>>=(const value_type& rhs)
            {
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ((this->underlying_index(I) >>= rhs), ...);
                }(std::make_index_sequence<this->underlying_size()>{});

                return *this;
            }

            constexpr fixed_valarray<bool, S> operator==(const fixed_valarray& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) == rhs.underlying_index(I)...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator==(const value_type& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) == rhs...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            friend constexpr fixed_valarray<bool, S> operator==(const value_type& lhs, const fixed_valarray& rhs)
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{lhs == rhs.underlying_index(I)...};
                }(std::make_index_sequence<rhs.underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator!=(const fixed_valarray& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) != rhs.underlying_index(I)...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator!=(const value_type& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) != rhs...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            friend constexpr fixed_valarray<bool, S> operator!=(const value_type& lhs, const fixed_valarray& rhs)
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{lhs != rhs.underlying_index(I)...};
                }(std::make_index_sequence<rhs.underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator<(const fixed_valarray& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) < rhs.underlying_index(I)...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator<(const value_type& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) < rhs...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            friend constexpr fixed_valarray<bool, S> operator<(const value_type& lhs, const fixed_valarray& rhs)
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{lhs < rhs.underlying_index(I)...};
                }(std::make_index_sequence<rhs.underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator<=(const fixed_valarray& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) <= rhs.underlying_index(I)...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator<=(const value_type& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) <= rhs...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            friend constexpr fixed_valarray<bool, S> operator<=(const value_type& lhs, const fixed_valarray& rhs)
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{lhs <= rhs.underlying_index(I)...};
                }(std::make_index_sequence<rhs.underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator>(const fixed_valarray& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) > rhs.underlying_index(I)...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator>(const value_type& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) > rhs...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            friend constexpr fixed_valarray<bool, S> operator>(const value_type& lhs, const fixed_valarray& rhs)
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{lhs > rhs.underlying_index(I)...};
                }(std::make_index_sequence<rhs.underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator>=(const fixed_valarray& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) >= rhs.underlying_index(I)...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            constexpr fixed_valarray<bool, S> operator>=(const value_type& rhs) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{this->underlying_index(I) >= rhs...};
                }(std::make_index_sequence<this->underlying_size()>{});
            }

            friend constexpr fixed_valarray<bool, S> operator>=(const value_type& lhs, const fixed_valarray& rhs)
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray<bool, S>{lhs >= rhs.underlying_index(I)...};
                }(std::make_index_sequence<rhs.underlying_size()>{});
            }

            friend constexpr void swap(fixed_valarray& lhs, fixed_valarray& rhs) noexcept
            {
                lhs.swap(rhs);
            }

            template<class F>
            fixed_valarray apply(F&& func) const
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return fixed_valarray{std::invoke(func, this->operator[](I))...};
                }(std::make_index_sequence<this->size()>{});
            }

            shift_expression<fixed_valarray> shift(std::make_signed_t<std::size_t> count) const
            {
                return {*this, count};
            }

            cshift_expression<fixed_valarray> cshift(std::make_signed_t<std::size_t> count) const
            {
                return {*this, count};
            }
        private:
            using underlying_valarray<T, S>::data_;
    };

    export
    template<std::derived_from<base_expression> E>
    fixed_valarray(const E&) -> fixed_valarray<typename E::value_type, E::base_type::size()>;

    export
    template<class... Ts>
    fixed_valarray(Ts&&...) -> fixed_valarray<std::common_type_t<std::decay_t<Ts>...>, sizeof...(Ts)>;
}
