#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace fastlib
{

    template <typename T>
    class Matrix
    {
        size_t rows_, cols_;
        std::vector<T> data_;

    public:
        Matrix(size_t r, size_t c, T init = T{})
            : rows_(r), cols_(c), data_(r * c, init) {}

        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }

        // Provide get/set for pybind11
        T get(size_t r, size_t c) const { return data_[r * cols_ + c]; }
        void set(size_t r, size_t c, T v) { data_[r * cols_ + c] = v; }

        // Optional nicer C++-side access
        T &operator()(size_t r, size_t c) { return data_[r * cols_ + c]; }
        const T &operator()(size_t r, size_t c) const { return data_[r * cols_ + c]; }

        std::string repr() const
        {
            std::ostringstream os;
            os << "Matrix(" << rows_ << "x" << cols_ << ")\n";
            for (size_t i = 0; i < rows_; ++i)
            {
                for (size_t j = 0; j < cols_; ++j)
                {
                    os << get(i, j) << " ";
                }
                os << "\n";
            }
            return os.str();
        }
    };

} // namespace fastlib
