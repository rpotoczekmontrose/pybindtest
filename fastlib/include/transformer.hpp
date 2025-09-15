#pragma once
#include <string>
#include "concepts.hpp"
#include "matrix.hpp"

namespace fastlib
{

    // Abstract base, templated
    template <Numeric T>
    class Transformer
    {
    public:
        virtual ~Transformer() = default;

        virtual std::string name() const = 0;
        virtual Matrix<T> apply(const Matrix<T> &m) const = 0;
    };

    // Concrete subclass
    template <Numeric T>
    class ScaleTransformer : public Transformer<T>
    {
        T factor_;

    public:
        ScaleTransformer(T factor) : factor_(factor) {}
        std::string name() const override { return "Scale"; }
        Matrix<T> apply(const Matrix<T> &m) const override
        {
            Matrix<T> out(m.rows(), m.cols(), T{});
            for (size_t i = 0; i < m.rows(); ++i)
            {
                for (size_t j = 0; j < m.cols(); ++j)
                {
                    out.set(i, j, m.get(i, j) * factor_);
                }
            }
            return out;
        }
    };

} // namespace fastlib
