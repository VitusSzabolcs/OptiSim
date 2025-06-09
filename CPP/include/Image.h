/**
* @file Image.h
* @brief This is the header file fot the Image class
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "ImagingSubject.h"

/**
 * @class Image
 * @brief Represents an image, specifically whether it's a "real" image.
 * 
 * This class extends ImagingSubject and adds a property ot indicate if
 * the image is real or virtual.
 */
class Image:public ImagingSubject{
    private:
        /**
         * @brief Indicates whether the image is real (true) or virtual (false).
         */
        bool real;
    public:
        /**
         * @brief Constructs a new Image object.
         */
        Image(double, double, bool);
        /**
         * @brief Sets the real/virtual status of the image.
         */
        void setReal(bool);
        /**
         * @brief Retrieves the real/virtual status of the image.
         * @return True if the image is real, false if it's virtual. 
         */
        bool getReal();
};

#endif // IMAGE_H