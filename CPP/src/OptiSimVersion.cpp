/**
* @file OptiSimVersion.cpp
* @brief Implements the function to retrieve the OptiSim library version string.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "OptiSimVersion.h" 

/**
 * @details This function provides direct access to the `OPTISIM_VERSION_STRING` macro,
 * which defines the current version of the OptiSim library in "MAJOR.MINOR.PATCH" format.
 * @return A constant C-style string representing the OptiSim library's version.
 */
const char* getOptiSimVersionString() {
    return OPTISIM_VERSION_STRING;
}