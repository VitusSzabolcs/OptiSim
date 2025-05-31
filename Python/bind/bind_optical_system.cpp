// bind_optical_system.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For std::vector, std::map, std::string exceptions
#include <pybind11/functional.h> // For lambda binding if needed
#include <sstream> // For stringstream to capture toString output

#include "OpticalSystem.h" // Your OpticalSystem header
#include "OpticalObject.h" // Base class
#include "Lens.h"          // Base for Thin/ThickLens
#include "ThinLens.h"      // Concrete lens types
#include "ThickLens.h"
#include "LightSource.h"   // Concrete object type
#include "Image.h"         // Return type for Calculate

namespace py = pybind11;

void bind_optical_system(py::module_ &m) {

    py::class_<OpticalSystem>(m, "OpticalSystem")
        // Constructors
        .def(py::init<>())
        .def(py::init<std::string>(), py::arg("file_name"))

        // Add methods
        // Overload for adding OpticalObject (Lenses)
        .def("add", static_cast<void(OpticalSystem::*)(OpticalObject&, std::string)>(&OpticalSystem::add),
             py::arg("optical_object"), py::arg("name"))
        // Overload for adding LightSource
        .def("add", static_cast<void(OpticalSystem::*)(LightSource)>(&OpticalSystem::add),
             py::arg("light_source"))

        // Modify methods
        .def("modifyLightSource", &OpticalSystem::modifyLightSource,
             py::arg("param"), py::arg("val"))
        .def("modifyOpticalObject", &OpticalSystem::modifyOpticalObject,
             py::arg("name"), py::arg("param"), py::arg("val"))

        // Other methods
        .def("getImageSequence", &OpticalSystem::getImageSequence)
        .def("Calculate", &OpticalSystem::Calculate)
        // toString method: Capture ostream output to std::string for Python
        .def("toString", [](OpticalSystem &self) {
            std::stringstream ss;
            self.toString(ss);
            py::print(ss.str()); // Print to Python's stdout
        })
        .def("toString", [](OpticalSystem &self, const std::string& file_name) {
            std::ofstream ofs(file_name);
            if (!ofs.is_open()) {
                throw std::string("Failed to open file for writing: " + file_name);
            }
            self.toString(ofs);
            ofs.close();
        })
        .def("save", &OpticalSystem::save, py::arg("file_name"))
        .def("remove", &OpticalSystem::remove, py::arg("name"))
        .def("getSystemElements", &OpticalSystem::getSystemElements)
        .def("getLightSource", &OpticalSystem::getLightSource);
}