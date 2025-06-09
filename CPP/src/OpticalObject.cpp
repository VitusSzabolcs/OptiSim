/**
* @file OpticalObject.cpp
* @brief Implements the non-abstract methods of the OpticalObject base class.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "OpticalObject.h"
using namespace std;

/**
 * @details This protected constructor initializes the x-coordinate (position) of the optical object along the optical axis.
 * @param x The initial x-coordinate of the optical object.
 */
OpticalObject::OpticalObject(double x){
    this->x = x;
}

/**
 * @details This method returns the current x-coordinate (position) of the optical object.
 */
double OpticalObject::getX(){
    return x; 
}

/**
 * @details This method updates the x-coordinate (position) of the optical object.
 * @param x The new x-coordinate value.
 */
void OpticalObject::setX(double x){
    this->x = x;
}
