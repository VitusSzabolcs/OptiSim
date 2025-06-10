/**
* @file bind_imaging_subjects.cpp
* @brief Defines the bind_imaging_subjects function
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include <pybind11/pybind11.h>
#include "ImagingSubject.h" 
#include "LightSource.h"    
#include "Image.h"

namespace py = pybind11;

/**
 * @brief Binds the C++ `ImagingSubject` class and its derived classes to Python.
 *
 * This function defines the Python interface for `ImagingSubject`, `LightSource`,
 * and `Image` classes, making their constructors and methods accessible from Python.
 *
 * @param m A reference to the pybind11 module to which the classes will be bound.
 */
void bind_imaging_subjects(py::module_& m) {
    /**
     * @brief Python binding for the `ImagingSubject` base class.
     *
     * Represents an abstract subject within the imaging simulation, possessing
     * X and Y coordinates.
     */
    py::class_<ImagingSubject>(m, "ImagingSubject", "Abstract base class for all imaging subjects with X and Y coordinates.")
        .def("getX", &ImagingSubject::getX, "Gets the X-coordinate of the subject.")
        .def("setX", &ImagingSubject::setX, "Sets the X-coordinate of the subject.")
        .def("getY", &ImagingSubject::getY, "Gets the Y-coordinate of the subject.")
        .def("setY", &ImagingSubject::setY, "Sets the Y-coordinate of the subject.");

    /**
     * @brief Python binding for the `LightSource` class, derived from `ImagingSubject`.
     *
     * Represents a light-emitting source within the imaging simulation.
     */
    py::class_<LightSource, ImagingSubject>(m, "LightSource", "Represents a point light source in the simulation.")
        .def(py::init<double, double>(),
             py::arg("x"), py::arg("y"),
             "Initializes a LightSource with specified X and Y coordinates.");

    /**
     * @brief Python binding for the `Image` class, derived from `ImagingSubject`.
     *
     * Represents an image formed by light, which can be real or virtual.
     */
    py::class_<Image, ImagingSubject>(m, "Image", "Represents an image (real or virtual) in the simulation.")
        .def(py::init<double, double, bool>(),
             py::arg("x"), py::arg("y"), py::arg("is_real"),
             "Initializes an Image with specified X, Y coordinates, and real/virtual status.")
        .def("getReal", &Image::getReal, "Checks if the image is real (True) or virtual (False).")
        .def("setReal", &Image::setReal, "Sets the real/virtual status of the image.");
}