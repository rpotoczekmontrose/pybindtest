#pragma once
#include <array>
#include <cstddef>
#include <string>
#include <sstream>

namespace fastlib
{

    template <typename T, std::size_t N>
    struct StaticMatrix
    {
        std::array<T, N * N> data{};

        constexpr StaticMatrix() = default;

        constexpr T get(std::size_t r, std::size_t c) const { return data[r * N + c]; }
        constexpr void set(std::size_t r, std::size_t c, T v) { data[r * N + c] = v; }

        constexpr std::size_t rows() const noexcept { return N; }
        constexpr std::size_t cols() const noexcept { return N; }

        static constexpr StaticMatrix<T, N> identity()
        {
            StaticMatrix<T, N> m{};
            for (std::size_t i = 0; i < N; ++i)
                m.set(i, i, T{1});
            return m;
        }

        std::string repr() const
        {
            std::ostringstream o;
            o << "StaticMatrix(" << N << "x" << N << ")";
            return o.str();
        }
    };

} // namespace fastlib
