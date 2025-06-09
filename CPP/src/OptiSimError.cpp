/**
* @file OptiSimError.cpp
* @brief Implements the OptiSimError custom exception class.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/
#include "OptiSimError.h"

/**
 * @details This constructor initializes the exception with a specific error message.
 * The provided string `msg` is copied into the `message` member variable.
 * @param msg A constant reference to a string containing the detailed error message.
 */
OptiSimError::OptiSimError(const string& msg):message(msg){}

/**
 * @details This method overrides the `std::exception::what()` method to provide a C-style string
 * representation of the error message. It is guaranteed not to throw any exceptions itself.
 */
const char* OptiSimError::what() const noexcept {
    return message.c_str();
}