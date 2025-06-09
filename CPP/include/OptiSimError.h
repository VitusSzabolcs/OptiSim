/**
* @file OptiSimError.h
* @brief Defines the custom exception class for OptiSim errors.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef OPTISIMERROR_H
#define OPTISIMERROR_H

#include <exception> // Required for inheriting from std::exception
#include <string>    // Required for std::string to store the error message

using namespace std;

/**
 * @class OptiSimError
 * @brief Custom exception class for handling errors within the OptiSim library.
 *
 * This class inherits from `std::exception` and provides a mechanism to
 * throw and catch specific errors that occur during the simulation or
 * configuration of optical systems. It stores a descriptive message about the error.
 */
class OptiSimError : public exception{
    private:
        /**
         * @brief Stores the detailed error message for this exception.
         */
        string message;
    public:

        /**
         * @brief Constructs an OptiSimError with a specific error message.
         */
        explicit OptiSimError(const string&);

        /**
         * @brief Returns a C-style string describing the error.
         * @details This method overrides `std::exception::what()` and provides
         * the stored error message.
         * @return A constant C-style string (char*) containing the error message.
         * @noexcept This function is guaranteed not to throw exceptions.
         */
        const char* what() const noexcept override;
};

#endif // OPTISIMERROR_H