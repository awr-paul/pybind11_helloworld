#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>

namespace py = pybind11;

void hello(const py::array& arr) {
    std::cout << "hello world! Got an array with " << arr.size() << " total elements" << std::endl;
    return;
}

PYBIND11_MODULE(submodule, m) {
    try {
        py::module_::import("numpy");
    } catch (...) {
        return;
    }
    m.doc() = "My docstring";
    m.def("hello", &hello, "A function that takes an numpy array object");
}
