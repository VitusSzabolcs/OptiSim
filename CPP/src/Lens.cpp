/**
* @file Lens.cpp
* @brief Implements the Lens class.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "Lens.h"
#include <iostream>
#include "OptiSimError.h"

using namespace std;

/**
 * @details This protected constructor initializes the lens's position and sets its focal length.
 * It includes a check to ensure the focal length is not zero, as this would represent an invalid lens state.
 * @param x The position along the optical axis (inherited from OpticalObject).
 * @param f The focal length of the lens.
 * @throws OptiSimError If the provided focal length `f` is zero.
 */
Lens::Lens(double x, double f):OpticalObject(x){
    if (f == 0) throw OptiSimError("ERROR: \tFocal length cannot be zero.");
    this->f = f;
}

/**
 * @details This method returns the focal length of the lens.
 */
double Lens::getF(){
    return f;
}