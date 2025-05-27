#include <pybind11/pybind11.h>
#include "ImagingSubject.h" 
#include "LightSource.h"    
#include "Image.h"

namespace py = pybind11;

// Function to bind ImagingSubject and its derived classes
void bind_imaging_subjects(py::module_& m) {
    py::class_<ImagingSubject>(m, "ImagingSubject")
        .def("getX", &ImagingSubject::getX)
        .def("setX", &ImagingSubject::setX)
        .def("getY", &ImagingSubject::getY)
        .def("setY", &ImagingSubject::setY);

    py::class_<LightSource, ImagingSubject>(m, "LightSource")
        .def(py::init<double, double>(), py::arg("x"), py::arg("y"));

    py::class_<Image, ImagingSubject>(m, "Image")
        .def(py::init<double, double, bool>(), py::arg("x"), py::arg("y"), py::arg("is_real"))
        .def("getReal", &Image::getReal)
        .def("setReal", &Image::setReal);
}