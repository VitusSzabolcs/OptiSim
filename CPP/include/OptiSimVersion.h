/**
* @file OptiSimVersion.h
* @brief Defines version information for the OptiSim library.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* This header provides macros for defining the major, minor, and patch
* versions of the OptiSim library, and a utility function to retrieve
* the full version string.
* @date 2025-06-09
*/

#ifndef OPTISIMVERSION_H
#define OPTISIMVERSION_H

/**
 * @brief The major version number of the OptiSim library.
 */
#define OPTISIM_VERSION_MAJOR "1"

/**
 * @brief The minor version number of the OptiSim library.
 */
#define OPTISIM_VERSION_MINOR "0"

/**
 * @brief The patch version number of the OptiSim library.
 */
#define OPTISIM_VERSION_PATCH "0"

/**
 * @brief Combines the major, minor, and patch versions into a single string.
 * @details This macro concatenates the individual version components
 * into a "MAJOR.MINOR.PATCH" format.
 */
#define OPTISIM_VERSION_STRING \
    OPTISIM_VERSION_MAJOR "." \
    OPTISIM_VERSION_MINOR "." \
    OPTISIM_VERSION_PATCH

/**
 * @brief Retrieves the full version string of the OptiSim library.
 * @return A constant C-style string containing the OptiSim library version (e.g., "1.0.0").
 */
const char* getOptiSimVersionString();

#endif // OPTISIMVERSION_H