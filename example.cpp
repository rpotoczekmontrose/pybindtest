#include <pybind11/pybind11.h>
#include <iostream>
#include <optional>
#include <string>


namespace py = pybind11;
// optional can be used as the return type of a factory that may fail
std::optional<std::string> create(bool b)
{
    if (b)
        return "Godzilla";
    return {};
}
 
// std::nullopt can be used to create any (empty) std::optional
auto create2(bool b)
{
    return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}

PYBIND11_MODULE(example, m) {
    // py::class_<Blob>(m, "Blob")
    //     .def(py::init<std::string>())
    //     .def_readwrite("data", &Blob::data);
    m.def("create", &set<int>);
    m.def("set", &set<std::string>);
    m.def("make_blob_bad", &make_blob_bad,
          py::return_value_policy::reference);
}
