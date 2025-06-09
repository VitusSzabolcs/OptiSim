/**
* @file Lens.h
* @brief Defines the Lens class, inheriting from OpticalObject.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef LENS_H
#define LENS_H

#include "OpticalObject.h"

/**
 * @class Lens
 * @brief Represents a basic lens with a focal length.
 *
 * This class extends OpticalObject and introduces the concept of focal length ('f'),
 * a critical property for lenses in optics. Its constructor is protected, indicating
 * it's meant to be a base class for more specific lens types.
 */
class Lens: public OpticalObject{
    protected:
        /**
         * @brief Constructs a new Lens object with specified position and focal length.
         */
        Lens(double, double);

        /**
         * @brief The focal length of the lens.
         *
         * This value determines the optical power of the lens.
         */
        double f;

    public:
        /**
         * @brief Retrieves the focal length of the lens.
         * @return The current focal length ('f') of the lens.
         */
        double getF();
};

#endif // LENS_H