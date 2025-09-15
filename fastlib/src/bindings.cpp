#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "matrix.hpp"
#include "transformer.hpp"
#include "parallel.hpp"
#include "computations.hpp"
#include "math_utils.hpp"
#include "static_matrix.hpp"

namespace py = pybind11;
using namespace fastlib;

// Trampoline for Transformer<T>
template <typename T>
class PyTransformer : public Transformer<T>
{
public:
    using Transformer<T>::Transformer;

    std::string name() const override
    {
        PYBIND11_OVERRIDE_PURE(
            std::string,    // return type
            Transformer<T>, // parent class
            name            // method name
        );
    }

    Matrix<T> apply(const Matrix<T> &m) const override
    {
        PYBIND11_OVERRIDE_PURE(
            Matrix<T>,
            Transformer<T>,
            apply,
            m);
    }
};

// Explicit binding for double
PYBIND11_MODULE(fastlib, m)
{
    // Bind Matrix<double>
    py::class_<Matrix<double>>(m, "Matrix")
        .def(py::init<size_t, size_t, double>())
        .def("rows", &Matrix<double>::rows)
        .def("cols", &Matrix<double>::cols)
        .def("get", &Matrix<double>::get)
        .def("set", &Matrix<double>::set)
        .def("repr", &Matrix<double>::repr);

    // Bind Transformer<double> with trampoline
    py::class_<Transformer<double>, PyTransformer<double>, std::shared_ptr<Transformer<double>>>(m, "Transformer")
        .def(py::init<>())
        .def("name", &Transformer<double>::name)
        .def("apply", &Transformer<double>::apply);

    // Bind ScaleTransformer<double>
    py::class_<ScaleTransformer<double>, Transformer<double>, std::shared_ptr<ScaleTransformer<double>>>(m, "ScaleTransformer")
        .def(py::init<double>())
        .def("name", &ScaleTransformer<double>::name)
        .def("apply", &ScaleTransformer<double>::apply);

    // Bind Transformer<int> (with trampoline, if needed later)
    py::class_<Transformer<int>, PyTransformer<int>, std::shared_ptr<Transformer<int>>>(m, "TransformerInt")
        .def(py::init<>())
        .def("name", &Transformer<int>::name)
        .def("apply", &Transformer<int>::apply);

    // Bind ScaleTransformer<int>
    py::class_<ScaleTransformer<int>, Transformer<int>, std::shared_ptr<ScaleTransformer<int>>>(m, "ScaleTransformerInt")
        .def(py::init<int>())
        .def("name", &ScaleTransformer<int>::name)
        .def("apply", &ScaleTransformer<int>::apply);

    // C++ free functions
    m.def("row_norms", &row_norms, "Compute parallel row norms of a matrix");
    m.def("identity", &identity, "Return an identity matrix", py::arg("n"));

    // Bind safe_divide for int and double explicitly
    m.def("safe_divide_int", &safe_divide<int>, "Safe integer division");
    m.def("safe_divide_double", &safe_divide<double>, "Safe floating-point division");

    // Bind StaticMatrix<double, 2>
    py::class_<StaticMatrix<double, 2>>(m, "StaticMatrix2d")
        .def(py::init<>())
        .def("rows", &StaticMatrix<double, 2>::rows)
        .def("cols", &StaticMatrix<double, 2>::cols)
        .def("__getitem__", [](const StaticMatrix<double, 2> &M, std::pair<size_t, size_t> idx)
             { return M.get(idx.first, idx.second); })
        .def("__setitem__", [](StaticMatrix<double, 2> &M, std::pair<size_t, size_t> idx, double val)
             { M.set(idx.first, idx.second, val); })
        .def("__repr__", &StaticMatrix<double, 2>::repr)
        .def_static("identity", &StaticMatrix<double, 2>::identity);

    // Bind StaticMatrix<double, 3>
    py::class_<StaticMatrix<double, 3>>(m, "StaticMatrix3d")
        .def(py::init<>())
        .def("rows", &StaticMatrix<double, 3>::rows)
        .def("cols", &StaticMatrix<double, 3>::cols)
        .def("__getitem__", [](const StaticMatrix<double, 3> &M, std::pair<size_t, size_t> idx)
             { return M.get(idx.first, idx.second); })
        .def("__setitem__", [](StaticMatrix<double, 3> &M, std::pair<size_t, size_t> idx, double val)
             { M.set(idx.first, idx.second, val); })
        .def("__repr__", &StaticMatrix<double, 3>::repr)
        .def_static("identity", &StaticMatrix<double, 3>::identity);
}
