#pragma once
#include <vector>
#include "../include/matrix.hpp"

namespace fastlib
{

    // Computes the Euclidean norm of each row in the matrix.
    std::vector<double> row_norms(const Matrix<double> &m);

    // Returns an identity matrix of size n x n.
    Matrix<double> identity(size_t n);

} // namespace fastlib