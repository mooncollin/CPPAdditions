export module cmoon.fixed_valarray.underlying;

import std.core;

namespace cmoon
{
    export
    template<class T, std::size_t S>
    struct underlying_valarray
    {
        using value_type     = T;
        using underlying     = std::array<value_type, S>;

        [[nodiscard]] constexpr const value_type& operator[](std::size_t pos) const noexcept
        {
            return data_[pos];
        }

        [[nodiscard]] constexpr value_type& operator[](std::size_t pos) noexcept
        {
            return data_[pos];
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

        constexpr value_type sum() const
        {
            return std::reduce(begin(), end());
        }

        constexpr value_type min() const
        {
            return *(std::ranges::min_element(data_));
        }

        constexpr value_type max() const
        {
            return *(std::ranges::max_element(data_));
        }

        constexpr void swap(underlying_valarray& other) noexcept
        {
            std::swap(data_, other.data_);
        }

        underlying data_;
    };
}