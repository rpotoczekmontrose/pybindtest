#include "../include/matrix.hpp"
#include "../include/parallel.hpp"
#include <cmath>
#include <vector>

namespace fastlib
{
    std::vector<double> row_norms(const Matrix<double> &m)
    {
        auto mapf = [&](size_t i)
        {
            double s = 0.0;
            for (size_t j = 0; j < m.cols(); ++j)
                s += m(i, j) * m(i, j);
            return std::sqrt(s);
        };
        std::vector<size_t> idx(m.rows());
        for (size_t i = 0; i < m.rows(); ++i)
            idx[i] = i;
        auto res = parallel_map(idx.begin(), idx.end(), mapf);
        return res;
    }

    Matrix<double> identity(size_t n)
    {
        Matrix<double> I(n, n, 0.0);
        for (size_t i = 0; i < n; ++i)
            I(i, i) = 1.0;
        return I;
    }
} // namespace fastlib