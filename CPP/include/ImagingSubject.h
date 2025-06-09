/**
* @file ImagingSubject.h
* @brief Defines the base class for imaging subjects.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/


/**
 * @class ImagingSubject
 * @brief A base class representing a subject within an imaging system.
 *
 * This class provides fundamental properties like x and y coordinates for any
 * object that can be part of an imaging process. It uses a protected constructor,
 * meaning it's primarily intended to be subclassed by other classes (like `Image`).
 */
#ifndef IMAGINGSUBJECT_H
#define IMAGINGSUBJECT_H

class ImagingSubject{
    protected:
        /**
         * @brief Constructs an ImagingSubject with given coordinates.
         */
        ImagingSubject(double, double);

        /**
         * @brief The x-coordinate of the imaging subject.
         */
        double x;

        /**
         * @brief The y-coordinate of the imaging subject.
         */
        double y;
    public:
        /**
         * @brief Retrieves the x-coordinate of the imaging subject.
         * @return The current x-coordinate.
         */
        double getX();

        /**
         * @brief Sets the x-coordinate of the imaging subject.
         */
        void setX(double);

        /**
         * @brief Retrieves the y-coordinate of the imaging subject.
         * @return The current y-coordinate.
         */
        double getY();

        /**
         * @brief Sets the y-coordinate of the imaging subject.
         */
        void setY(double);
};

#endif // IMAGINGSUBJECT_H