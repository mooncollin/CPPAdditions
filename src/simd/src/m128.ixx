module;

#include <xmmintrin.h>

export module cmoon.simd.m128;

import std.core;

namespace cmoon::simd
{
    export
    struct m128
    {
        using simd_type = __m128;
        using value_type = float;

        simd_type data;

        [[nodiscard]] static constexpr std::size_t size() noexcept
        {
            return 4;
        }

        class reference
        {
            public:
                operator value_type() const noexcept
                {
                    alignas(16) value_type buf[size()];
                    _mm_store_ps(buf, owner->data);
                    return buf[i];
                }

                reference& operator=(value_type v) noexcept
                {
                    alignas(16) value_type buf[size()];
                    _mm_store_ps(buf, owner->data);
                    buf[i] = v;
                    *owner = _mm_load_ps(buf);
                    return *this;
                }
            private:
                friend struct m128;

                reference(m128& owner, std::size_t i) noexcept
                    : owner{std::addressof(owner)}, i{i} {}

                m128* owner;
                std::size_t i;
        };

        m128() noexcept = default;

        m128(simd_type data) noexcept
            : data{data} {}

        m128(float v1, float v2 = {}, float v3 = {}, float v4 = {}) noexcept
            : data{_mm_set_ps(v4, v3, v2, v1)} {}

        [[nodiscard]] m128 operator+(const m128& rhs) const noexcept
        {
            return {_mm_add_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator-(const m128& rhs) const noexcept
        {
            return {_mm_sub_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator*(const m128& rhs) const noexcept
        {
            return {_mm_mul_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator/(const m128& rhs) const noexcept
        {
            return {_mm_div_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator&(const m128& rhs) const noexcept
        {
            return {_mm_and_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator==(const m128& rhs) const noexcept
        {
            return {_mm_cmpeq_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator!=(const m128& rhs) const noexcept
        {
            return {_mm_cmpneq_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator<(const m128& rhs) const noexcept
        {
            return {_mm_cmplt_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator<=(const m128& rhs) const noexcept
        {
            return {_mm_cmple_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator>(const m128& rhs) const noexcept
        {
            return {_mm_cmpgt_ps(data, rhs.data)};
        }

        [[nodiscard]] m128 operator>=(const m128& rhs) const noexcept
        {
            return {_mm_cmpge_ps(data, rhs.data)};
        }

        [[nodiscard]] m128& operator+=(const m128& rhs) noexcept
        {
            *this = *this + rhs;
            return *this;
        }

        [[nodiscard]] m128& operator-=(const m128& rhs) noexcept
        {
            *this = *this - rhs;
            return *this;
        }

        [[nodiscard]] m128& operator*=(const m128& rhs) noexcept
        {
            *this = *this * rhs;
            return *this;
        }

        [[nodiscard]] m128& operator/=(const m128& rhs) noexcept
        {
            *this = *this / rhs;
            return *this;
        }

        [[nodiscard]] reference operator[](std::size_t i) noexcept
        {
            return {*this, i};
        }

        [[nodiscard]] value_type operator[](std::size_t i) const noexcept
        {
            alignas(16) value_type buf[size()];
            _mm_store_ps(buf, data);
            return buf[i];
        }
    };
}