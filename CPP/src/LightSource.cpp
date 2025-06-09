/**
* @file LightSource.cpp
* @brief Implements the LightSource class.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "LightSource.h"

/**
 * @details This constructor initializes the x and y coordinates of the light source by passing them to the base `ImagingSubject` constructor.
 * @param x The x-coordinate of the light source.
 * @param y The y-coordinate of the light source.
 */
LightSource::LightSource(double x, double y):ImagingSubject(x, y){};