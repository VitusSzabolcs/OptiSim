/**
* @file bind_optical_objects.cpp
* @brief Defines the bind_optical_objects function
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include <pybind11/pybind11.h>
#include "OpticalObject.h" 
#include "Lens.h"    
#include "ThickLens.h"
#include "ThinLens.h"

namespace py = pybind11;

/**
 * @brief Binds the C++ `OpticalObject` class and its derived classes to Python.
 *
 * This function defines the Python interface for `OpticalObject`, `Lens`,
 * `ThinLens`, and `ThickLens` classes, making their constructors and methods
 * accessible from Python.
 *
 * @param m A reference to the pybind11 module to which the classes will be bound.
 */
void bind_optical_objects(py::module_& m) {
    /**
     * @brief Python binding for the `OpticalObject` base class.
     *
     * Represents an abstract optical component with a position along the optical axis.
     */
    py::class_<OpticalObject>(m, "OpticalObject", "Abstract base class for all optical components.")
        .def("getX", &OpticalObject::getX, "Gets the X-coordinate (position along the optical axis) of the object.")
        .def("setX", &OpticalObject::setX, py::arg("x"), "Sets the X-coordinate (position along the optical axis) of the object.");

    /**
     * @brief Python binding for the `Lens` base class, derived from `OpticalObject`.
     *
     * Represents an abstract lens with a focal length.
     */
    py::class_<Lens, OpticalObject>(m, "Lens", "Abstract base class for all lens types.")
        .def("getF", &Lens::getF, "Gets the focal length of the lens.");

    /**
     * @brief Python binding for the `ThinLens` class, derived from `Lens`.
     *
     * Represents an idealized thin lens with a single principal plane.
     */
    py::class_<ThinLens, Lens>(m, "ThinLens", "Represents an idealized thin lens.")
        .def(py::init<double, double>(), py::arg("x"), py::arg("f"),
             "Initializes a ThinLens with a specified X-coordinate and focal length.")
        .def("Calculate", &ThinLens::Calculate, py::arg("imaging_subject"),
             "Calculates the image formed by the thin lens for a given imaging subject.")
        .def("setF", &ThinLens::setF, py::arg("f"), "Sets the focal length of the thin lens.");

    /**
     * @brief Python binding for the `ThickLens` class, derived from `Lens`.
     *
     * Represents a real-world thick lens with non-negligible thickness and curved surfaces.
     */
    py::class_<ThickLens, Lens>(m, "ThickLens", "Represents a thick lens with two curved surfaces and finite thickness.")
        .def(py::init<double, double, double, double, double>(),
             py::arg("x"), py::arg("n"), py::arg("d"), py::arg("r_left"), py::arg("r_right"),
             "Initializes a ThickLens with X-coordinate, refractive index, thickness, and radii of curvature.")
        .def("Calculate", &ThickLens::Calculate, py::arg("imaging_subject"),
             "Calculates the image formed by the thick lens for a given imaging subject.")
        .def("getN", &ThickLens::getN, "Gets the refractive index of the lens material.")
        .def("setN", &ThickLens::setN, py::arg("n"), "Sets the refractive index of the lens material.")
        .def("getD", &ThickLens::getD, "Gets the thickness of the lens along the optical axis.")
        .def("setD", &ThickLens::setD, py::arg("d"), "Sets the thickness of the lens along the optical axis.")
        .def("getR_left", &ThickLens::getR_Left, "Gets the radius of curvature of the left surface.")
        .def("setR_left", &ThickLens::setR_Left, py::arg("r_left"), "Sets the radius of curvature of the left surface.")
        .def("getR_right", &ThickLens::getR_Right, "Gets the radius of curvature of the right surface.")
        .def("setR_right", &ThickLens::setR_Right, py::arg("r_right"), "Sets the radius of curvature of the right surface.");
}