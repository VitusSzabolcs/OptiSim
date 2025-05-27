#include <pybind11/pybind11.h>
#include "OpticalObject.h" 
#include "Lens.h"    
#include "ThickLens.h"
#include "ThinLens.h"

namespace py = pybind11;

// Function to bind ImagingSubject and its derived classes
void bind_optical_objects(py::module_& m) {
    py::class_<OpticalObject>(m, "OpticalObject")
        .def("getX", &OpticalObject::getX)
        .def("setX", &OpticalObject::setX, py::arg("x"));

    py::class_<Lens, OpticalObject>(m, "Lens")
        .def("getF", &Lens::getF);

    py::class_<ThinLens, Lens>(m, "ThinLens")
        .def(py::init<double, double>(), py::arg("x"), py::arg("f"))
        .def("Calculate", &ThinLens::Calculate, py::arg("imaging_subject"))
        .def("setF", &ThinLens::setF, py::arg("f"));

    py::class_<ThickLens, Lens>(m, "ThickLens")
        .def(py::init<double, double, double, double, double>(),
             py::arg("x"), py::arg("n"), py::arg("d"), py::arg("r_left"), py::arg("r_right"))
        .def("Calculate", &ThickLens::Calculate, py::arg("imaging_subject"))
        .def("getN", &ThickLens::getN)
        .def("setN", &ThickLens::setN, py::arg("n"))
        .def("getD", &ThickLens::getD)
        .def("setD", &ThickLens::setD, py::arg("d"))
        .def("getR_left", &ThickLens::getR_Left)
        .def("setR_left", &ThickLens::setR_Left, py::arg("r_left"))
        .def("getR_right", &ThickLens::getR_Right)
        .def("setR_right", &ThickLens::setR_Right, py::arg("r_right"));
}