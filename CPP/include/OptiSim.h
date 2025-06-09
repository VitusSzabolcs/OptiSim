/**
 * @file OptiSim.h
 * @brief Main header file for the OptiSim optical simulation library.
 *
 * This header aggregates all public interfaces for the OptiSim library,
 * providing a convenient way to include all necessary components for
 * building and simulating optical systems.
 *
 * @mainpage OptiSim Library Documentation
 *
 * @section intro_sec Introduction
 * The OptiSim library is designed to facilitate the simulation and analysis of
 * optical systems. It provides classes for representing light sources, images,
 * various types of lenses (thin and thick), and mechanisms to assemble these
 * into a complete optical system for calculations and ray tracing.
 *
 * @section features_sec Features
 * - **Modular Design:** Components like `LightSource`, `Image`, `Lens`, `OpticalObject` are
 * designed as distinct classes for easy integration and extension.
 * - **Thin and Thick Lenses:** Supports different lens models for varied simulation needs.
 * - **System Management:** The `OpticalSystem` class allows users to build, modify,
 * calculate, and save complex optical setups.
 * - **Ray Tracing:** Capable of tracing representative rays through the system for visualization.
 * - **Error Handling:** Robust error handling through custom exceptions (`OptiSimError`).
 *
 * @section getting_started_sec Getting Started
 * To use the OptiSim library, simply include this `OptiSim.h` header in your
 * project. Ensure all source files (`.cpp`) are compiled and linked correctly.
 *
 *
* @file OptiSim.h
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef OPTISIM_H
#define OPTISIM_H

// Core components of the optical simulation
#include "Image.h"          ///< @brief Represents an image formed by optical elements.
#include "ImagingSubject.h" ///< @brief Base class for objects that can be imaged.
#include "Lens.h"           ///< @brief Abstract base class for lenses.
#include "LightSource.h"    ///< @brief Represents a point light source.
#include "OpticalObject.h"  ///< @brief Abstract base class for objects on the optical axis.
#include "OpticalSystem.h"  ///< @brief Manages and simulates a collection of optical elements.
#include "ThickLens.h"      ///< @brief Represents a thick lens with specified radii, thickness, and refractive index.
#include "ThinLens.h"       ///< @brief Represents a thin lens with a single focal length.

// Utility and versioning
#include "OptiSimVersion.h" ///< @brief Contains version information for the OptiSim library.
#include "OptiSimError.h"   ///< @brief Custom exception class for OptiSim specific errors.

#endif // OPTISIM_H