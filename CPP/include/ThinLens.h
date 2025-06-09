/**
* @file ThinLens.h
* @brief Defines the ThinLens class, representing an idealized thin lens.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef THINLENS_H
#define THINLENS_H

#include "Lens.h"           // Inherits from the base Lens class

/**
 * @class ThinLens
 * @brief Represents an idealized thin lens in an optical system.
 *
 * This class extends the basic `Lens` by implementing the simplified thin lens
 * formula, where the lens is assumed to have no thickness and the principal
 * planes coincide at the lens's center. It provides methods to calculate
 * the image formed by the lens and to set its focal length.
 */
class ThinLens: public Lens{
    public:

        /**
         * @brief Constructs a new ThinLens object.
         */
        ThinLens(double, double);

        /**
         * @brief Calculates the image formed by this thin lens.
         * @return An `Image` object representing the calculated image.
         */
        Image Calculate(ImagingSubject) override;

        /**
         * @brief Sets the focal length of the thin lens.
         */
        void setF(double);
};

#endif // THINLENS_H