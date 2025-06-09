/**
* @file ThinLens.cpp
* @brief Implementation of the ThinLens class for modeling idealized thin lenses.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "ThinLens.h"
#include <cmath>            // For std::isinf, std::abs
#include <limits>           // For std::numeric_limits
#include <iostream>         // For debugging output (if needed)
#include "OptiSimError.h"   // Custom exception class

using namespace std;

/**
 * @details Initializes the thin lens with its position on the optical axis and its focal length.
 * The position `x` represents the location of the lens's optical center.
 * @param x The position of the thin lens on the optical axis.
 * @param f The focal length of the thin lens.
 */
ThinLens::ThinLens(double x, double f):Lens(x, f){}

/**
 * @details This method implements the thin lens formula to determine the image's
 * position, size, and whether it is real or virtual. The object distance `d_is`
 * is calculated relative to the lens's own position (`x`).
 *
 * @param is The `ImagingSubject` (object) to be imaged by the lens. This includes
 * its x-coordinate and y-coordinate (height/size).
 */
Image ThinLens::Calculate(ImagingSubject is){
    double d_is = x - is.getX();
    double y_is = is.getY();

    double d_im;
    double y_im;
    bool is_real;

    if (isinf(d_is)) {
        d_im = f;
        y_im = 0.0;
        is_real = (f > 0);
    } else {
        double denominator = d_is - f;

        if (abs(denominator) < numeric_limits<double>::epsilon()) {
            y_im = numeric_limits<double>::infinity();
            if (f > 0) {
                d_im = numeric_limits<double>::infinity();
                is_real = true;
            } else {
                d_im = -numeric_limits<double>::infinity();
                is_real = false;
            }
        } else {
            d_im = (f * d_is) / denominator;
            y_im = -d_im / d_is * y_is;
            is_real = d_im > 0;
        }
    }

    return Image(x + d_im, y_im, is_real);
}

/**
 * @details Updates the focal length (`f`) of the thin lens to the new provided value.
 * This method includes a validation check to prevent setting the focal length to zero,
 * as this would represent an infinite power lens, which is undefined in this context.
 * @throws OptiSimError if the provided focal length `f` is zero.
 * @param f The new focal length for the lens.
 */
void ThinLens::setF(double f){
    if (f == 0) throw OptiSimError("ERROR: \tFocal length cannot be zero.");
    this->f = f;
}