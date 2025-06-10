/**
* @file optisim_bindings.cpp
* @brief The main pybind module
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include <pybind11/pybind11.h>
#include <iostream>
#include "OptiSimError.h"

namespace py = pybind11;

// Forward declarations for binding functions
void bind_imaging_subjects(py::module_& m);
void bind_optical_objects(py::module_& m);
void bind_optical_system(py::module_& m);

/**
 * @brief Main pybind11 module definition for the OptiSim library.
 *
 * This is the entry point for the Python module. It defines the module-level
 * docstring and calls the individual binding functions to expose the
 * various C++ classes and functionalities to Python. It also registers
 * custom C++ exceptions to be handled in Python.
 *
 * @param m A reference to the pybind11 module object.
 */
PYBIND11_MODULE(optisim, m) {
    // Module-level docstring (visible when you 'help(optisim)' in Python)
    m.doc() = "OptiSim: A C++ Optical Simulation Library bound to Python using pybind11.";

    // Call individual binding functions to populate the module
    bind_optical_objects(m);
    bind_imaging_subjects(m);
    bind_optical_system(m);

    /**
     * @brief Registers the custom `OptiSimError` C++ exception as a Python exception.
     *
     * This allows `OptiSimError` exceptions thrown in the C++ backend to be
     * caught and handled as `optisim.OptiSimError` in Python.
     */
    py::register_exception<OptiSimError>(m, "OptiSimError");
}
