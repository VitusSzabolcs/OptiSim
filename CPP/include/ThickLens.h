/**
* @file ThickLens.h
* @brief Defines the ThickLens class, representing a lens with physical thickness.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#ifndef THICKLENS_H
#define THICKLENS_H

#include "Lens.h" // Inherits from the base Lens class

/**
 * @class ThickLens
 * @brief Represents a thick lens in an optical system.
 *
 * This class extends the basic `Lens` by incorporating additional physical properties
 * such as refractive index, thickness, and radii of curvature for both surfaces.
 * It provides methods to calculate the effective focal length and to compute
 * the image formed by the lens, taking into account its thickness.
 */
class ThickLens: public Lens{
    private:
        /**
         * @brief The refractive index of the lens material.
         * @details This value 'n' determines how much light bends as it passes through the lens.
         */
        double n;

        /**
         * @brief The radius of curvature of the left surface of the lens.
         * @details A positive value typically indicates a convex surface (center of curvature to the right),
         * and a negative value indicates a concave surface (center of curvature to the left).
         */
        double r_left;

        /**
         * @brief The radius of curvature of the right surface of the lens.
         * @details A positive value typically indicates a concave surface (center of curvature to the left),
         * and a negative value indicates a convex surface (center of curvature to the right).
         */
        double r_right;

        /**
         * @brief The axial thickness of the lens.
         * @details This is the distance between the two principal surfaces of the lens.
         */
        double d;

        /**
         * @brief Computes the effective focal length of the thick lens.
         * @return The calculated effective focal length of the thick lens.
         */
        double computeF(double, double, double, double);

        /**
         * @brief Computes the position of the left principal plane (H1).
         * @return The distance of the left principal plane from the left vertex.
         */
        double computeHLeft();

        /**
         * @brief Computes the position of the right principal plane (H2).
         * @return The distance of the right principal plane from the right vertex.
         */
        double computeHRight();
    
    public:
        /**
         * @brief Constructs a new ThickLens object.
         */
        ThickLens(double, double, double, double, double);

        /**
         * @brief Retrieves the refractive index of the lens.
         * @return The refractive index (n) of the lens material.
         */
        double getN();

        /**
         * @brief Sets the refractive index of the lens.
         */
        void setN(double);

        /**
         * @brief Retrieves the radius of curvature of the left lens surface.
         * @return The radius of curvature (r_left) of the left surface.
         */
        double getR_Left();

        /**
         * @brief Sets the radius of curvature of the left lens surface.
         */
        void setR_Left(double);

        /**
         * @brief Retrieves the radius of curvature of the right lens surface.
         * @return The radius of curvature (r_right) of the right surface.
         */
        double getR_Right();

        /**
         * @brief Sets the radius of curvature of the right lens surface.
         */
        void setR_Right(double);

        /**
         * @brief Retrieves the axial thickness of the lens.
         * @return The axial thickness (d) of the lens.
         */
        double getD();

        /**
         * @brief Sets the axial thickness of the lens.
         */
        void setD(double);

        /**
         * @brief Calculates the image formed by this thick lens.
         * @return An `Image` object representing the calculated image.
         */
        Image Calculate(ImagingSubject) override;
};

#endif // THICKLENS_H