/**
* @file OpticalObject.h
* @brief Defines the abstract base class for all optical objects in the system.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef OPTICALOBJECT_H
#define OPTICALOBJECT_H

#include "Image.h"          // Required for the return type of Calculate
#include "ImagingSubject.h" // Required for the parameter type of Calculate
#include "LightSource.h"    // Potentially relevant for future derived classes, though not directly used here

/**
 * @class OpticalObject
 * @brief An abstract base class for any object positioned on the optical axis.
 *
 * This class serves as a fundamental building block for an optical simulation.
 * It provides a common position along the optical axis (x-coordinate) and
 * defines an abstract interface for calculating the image formed by the object.
 *
 * @note This is an abstract class, meaning it cannot be instantiated directly.
 * Derived classes must implement the pure virtual `Calculate` method.
 */
class OpticalObject{

    protected:
        /**
         * @brief Constructs an OpticalObject at a specified position on the optical axis.
         */
        OpticalObject(double);

        /**
         * @brief The x-coordinate representing the position of the optical object along the optical axis.
         */
        double x;
        
    public:

        /**
         * @brief Retrieves the x-coordinate (position) of the optical object.
         * @return The current x-coordinate of the object.
         */
        double getX();

        /**
         * @brief Sets the x-coordinate (position) of the optical object.
         */
        void setX(double);

        /**
         * @brief Pure virtual function to calculate the image formed by this optical object.
         *
         * This is an abstract method that must be implemented by any concrete derived class.
         * It defines the core behavior of an optical object: transforming an imaging subject into an image.
         *
         * @return An `Image` object representing the calculated image.
         */
        virtual Image Calculate(ImagingSubject) = 0;
};

#endif // OPTICALOBJECT_H
