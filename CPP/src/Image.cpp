/**
* @file Image.cpp
* @brief Implements the Image class, defining its constructor and methods.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "Image.h"

/**
 * @details This constructor initializes the base `ImagingSubject` part and then sets the `real` status.
 * @param x A double value for the x-coordinate (passed to ImagingSubject).
 * @param y A double value for the y-coordinate (passed to ImagingSubject).
 * @param real A boolean indicating whether the image is real (true) or virtual (false).
 */
Image::Image(double x, double y, bool real):ImagingSubject(x, y){
    this->real = real;
}

/**
 * @details This is a simple getter method that returns the current value of the `real` member.
 */
bool Image::getReal(){
    return real;
}

/**
 * @details This method updates the `real` member of the Image object.
 * @param real A boolean value; true to set the image as real, false to set it as virtual.
 */
void Image::setReal(bool real){
    this->real = real;
}