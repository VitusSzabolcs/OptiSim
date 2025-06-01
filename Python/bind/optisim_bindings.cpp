#include <pybind11/pybind11.h>
#include <iostream>
#include "OptiSimError.h"

namespace py = pybind11;

void bind_imaging_subjects(py::module_& m);
void bind_optical_objects(py::module_& m);
void bind_optical_system(py::module_& m);

PYBIND11_MODULE(optisim, m) {
    
    m.doc() = "OptiSim: A C++ Optical Simulation Library bound to Python using pybind11.";

    bind_optical_objects(m);
    bind_imaging_subjects(m);
    bind_optical_system(m);

    py::register_exception<OptiSimError>(m, "OptiSimError");
}
