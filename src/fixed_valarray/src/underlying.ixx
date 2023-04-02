export module cmoon.fixed_valarray.underlying;

import std.core;

import cmoon.simd;

namespace cmoon
{
    export
    template<class T, std::size_t S>
    struct underlying_valarray
    {
        using underlying = typename std::array<T, S>;

        underlying data_;

        constexpr underlying_valarray() = default;
        constexpr underlying_valarray(const underlying_valarray&) = default;
        constexpr underlying_valarray(underlying_valarray&&) noexcept = default;

        constexpr underlying_valarray& operator=(const underlying_valarray&) = default;
        constexpr underlying_valarray& operator=(underlying_valarray&&) noexcept = default;

        [[nodiscard]] static consteval std::size_t underlying_size() noexcept
        {
            return std::tuple_size_v<underlying>;
        }

        constexpr underlying_valarray(underlying u) noexcept
            : data_{std::move(u)} {}

        template<std::convertible_to<T>... Args>
        constexpr underlying_valarray(Args&&... args)
            : data_{std::forward<Args>(args)...} {}

        [[nodiscard]] constexpr const T& operator[](std::size_t i) const noexcept
        {
            return data_[i];
        }

        [[nodiscard]] constexpr T& operator[](std::size_t i) noexcept
        {
            return data_[i];
        }

        constexpr auto begin() noexcept
        {
            return data_.begin();
        }

        constexpr auto end() noexcept
        {
            return data_.end();
        }

        constexpr auto begin() const noexcept
        {
            return data_.begin();
        }

        constexpr auto end() const noexcept
        {
            return data_.end();
        }

        constexpr T sum() const
        {
            return std::reduce(begin(), end());
        }

        constexpr T min() const
        {
            return *(std::ranges::min_element(data_));
        }

        constexpr T max() const
        {
            return *(std::ranges::max_element(data_));
        }

        constexpr void swap(underlying_valarray& other) noexcept
        {
            std::swap(data_, other.data_);
        }
    };

    template<class T, std::size_t S>
    struct choose_simd_type;

    template<std::size_t S>
        requires(S > 1)
    struct choose_simd_type<float, S> : std::type_identity<cmoon::simd::m128> {};

    template<class T, std::size_t S>
    using choose_simd_type_t = typename choose_simd_type<T, S>::type;

    export
    template<typename T, std::size_t S>
        requires(requires {
            typename choose_simd_type<T, S>;
        })
    struct underlying_valarray<T, S>
    {
        using simd_type = choose_simd_type_t<T, S>;
        using underlying = typename std::array<simd_type, (S / simd_type::size()) +
                                                          static_cast<bool>(S % simd_type::size())>;

        underlying data_;

        [[nodiscard]] static consteval std::size_t underlying_size() noexcept
        {
            return std::tuple_size_v<underlying>;
        }
        private:
            template<std::size_t I, class Tup>
            [[nodiscard]] constexpr auto construct(Tup&& tup)
            {
                const auto get_helper = [&]<std::size_t I2> {
                    if constexpr (I >= std::tuple_size_v<Tup>)
                    {
                        return T{};
                    }
                    else
                    {
                        return std::get<I>(std::move(tup));
                    }
                };

                return [&]<std::size_t... I2>(std::index_sequence<I2...>) {
                    return simd_type{
                        get_helper.template operator()<I2 + I>()...
                    };
                }(std::make_index_sequence<simd_type::size()>{});
            }

            template<class... Args>
            [[nodiscard]] constexpr underlying constructor_helper(Args&&... args)
            {
                return [&]<std::size_t... I>(std::index_sequence<I...>) {
                    return underlying{
                        construct<I * simd_type::size()>(std::forward_as_tuple(std::forward<Args>(args)...))...
                    };
                }(std::make_index_sequence<underlying_size()>{});
            }
        public:
            constexpr underlying_valarray() = default;
            constexpr underlying_valarray(const underlying_valarray&) = default;
            constexpr underlying_valarray(underlying_valarray&&) noexcept = default;

            constexpr underlying_valarray& operator=(const underlying_valarray&) = default;
            constexpr underlying_valarray& operator=(underlying_valarray&&) noexcept = default;

            constexpr underlying_valarray(underlying u) noexcept
                : data_{std::move(u)} {}

            template<std::convertible_to<T>... Args>
            constexpr underlying_valarray(Args&&... args)
                : data_{constructor_helper(std::forward<Args>(args)...)} {}

            [[nodiscard]] constexpr auto operator[](std::size_t i) const noexcept
            {
                return data_[i / simd_type::size()][i % simd_type::size()];
            }

            [[nodiscard]] constexpr auto operator[](std::size_t i) noexcept
            {
                return data_[i / simd_type::size()][i % simd_type::size()];
            }

            // constexpr auto begin() noexcept
            // {
            //     return data_.begin();
            // }

            // constexpr auto end() noexcept
            // {
            //     return data_.end();
            // }

            // constexpr auto begin() const noexcept
            // {
            //     return data_.begin();
            // }

            // constexpr auto end() const noexcept
            // {
            //     return data_.end();
            // }

            // constexpr T sum() const
            // {
            //     return std::reduce(begin(), end());
            // }

            // constexpr T min() const
            // {
            //     return *(std::ranges::min_element(data_));
            // }

            // constexpr T max() const
            // {
            //     return *(std::ranges::max_element(data_));
            // }

            // constexpr void swap(underlying_valarray& other) noexcept
            // {
            //     std::swap(data_, other.data_);
            // }
    };
}