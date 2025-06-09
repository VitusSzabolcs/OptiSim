/**
* @file ImagingSubject.cpp
* @brief Implements the ImagingSubject class.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "ImagingSubject.h"

/**
 * @details This protected constructor initializes the x and y coordinates of the imaging subject.
 * @param x The initial x-coordinate.
 * @param y The initial y-coordinate.
 */
ImagingSubject::ImagingSubject(double x, double y){
    this->x = x;
    this->y = y;
}

/**
 * @details This method returns the current x-coordinate of the imaging subject.
 */
double ImagingSubject::getX(){
    return this->x;
}

/**
 * @details This method returns the current y-coordinate of the imaging subject.
 */
double ImagingSubject::getY(){
    return this->y;
}

/**
 * @details This method updates the x-coordinate of the imaging subject.
 * @param x The new x-coordinate value.
 */
void ImagingSubject::setX(double x){
    this->x = x;
}

/**
 * @details This method updates the y-coordinate of the imaging subject.
 * @param y The new y-coordinate value.
 */
void ImagingSubject::setY(double y){
    this->y = y;
}