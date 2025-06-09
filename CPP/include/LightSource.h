/**
* @file LightSource.h
* @brief Defines the LightSource class, representing a source of light.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "ImagingSubject.h"

/**
 * @class LightSource
 * @brief Represents a light source within an optical system.
 *
 * This class inherits from ImagingSubject, positioning a light source
 * within an optical setup using its x and y coordinates.
 */
class LightSource:public ImagingSubject{
    public:
        /**
         * @brief Constructs a new LightSource object.
         */
        LightSource(double, double);
};

#endif // LIGHTSOURCE_H