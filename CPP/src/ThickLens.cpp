/**
 * @file ThickLens.cpp
 * @brief Implementation of the ThickLens class for modeling thick lenses.
 */

#include "ThickLens.h"
#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <OptiSimError.h>

using namespace std;

/**
 * @brief Computes the focal length of a thick lens using the lensmaker's equation.
 * 
 * @param n Refractive index of the lens material
 * @param d Thickness of the lens
 * @param r_left Radius of curvature of the left lens surface
 * @param r_right Radius of curvature of the right lens surface
 * @return Computed focal length
 * @throws OptiSimError if r_left or r_right is zero
 */
double ThickLens::computeF(double n, double d, double r_left, double r_right){
    if(r_left == 0.0 || r_right == 0.0) {
        throw OptiSimError("ERROR: \tThe radius of the surface cannot be 0.");
    }

    double term1 = isinf(r_left) ? 0.0 : 1.0 / r_left;
    double term2 = isinf(r_right) ? 0.0 : 1.0 / r_right;

    double term3 = 0.0;
    if (!isinf(r_left) && !isinf(r_right)) {
        term3 = ((n - 1.0) * d) / (n * r_left * r_right);
    }
    
    double finv = (n - 1.0) * (term1 - term2 + term3);

    if (abs(finv) < numeric_limits<double>::epsilon()) {
        return numeric_limits<double>::infinity();
    } else {
        return 1.0 / finv;
    }
}

/**
 * @brief Computes the height of the left principal plane.
 * 
 * @return Height of the left principal plane relative to the lens center
 */
double ThickLens::computeHLeft(){
    return - f * (n - 1) * d / r_right / n + x - d/2;
}

/**
 * @brief Computes the height of the right principal plane.
 * 
 * @return Height of the right principal plane relative to the lens center
 */
double ThickLens::computeHRight(){
    return - f * (n - 1) * d / r_left / n + x + d/2;
}

/**
 * @brief Constructor for ThickLens.
 * 
 * @param x Position of the lens center
 * @param n Refractive index
 * @param d Thickness of the lens
 * @param r_left Radius of curvature of the left surface
 * @param r_right Radius of curvature of the right surface
 * @throws OptiSimError if n or d is non-positive
 */
ThickLens::ThickLens(double x, double n, double d, double r_left, double r_right):Lens(x, computeF(n, d, r_left, r_right)){
    if(n <= 0) throw OptiSimError("ERROR: \tThe refractive index must be a positive number.");
    if(d <= 0) throw OptiSimError("ERROR: \tThe thickness of the lens must be a positive number.");
    this->n = n;
    this->d = d;
    this->r_left = r_left;
    this->r_right = r_right;
}

/**
 * @brief Gets the refractive index of the lens.
 * @return The refractive index
 */
double ThickLens::getN(){
    return n;
}

/**
 * @brief Sets the refractive index of the lens and updates focal length.
 * 
 * @param n New refractive index
 * @throws OptiSimError if n is non-positive
 */
void ThickLens::setN(double n){
    if(n <= 0) throw OptiSimError("ERROR: \tThe refractive index must be a positive number.");
    if(this->n != n){
        this->n = n;
        this->f = computeF(n, d, r_left, r_right);
    }
}

/**
 * @brief Gets the thickness of the lens.
 * @return The thickness
 */
double ThickLens::getD(){
    return d;
}

/**
 * @brief Sets the thickness of the lens and updates focal length.
 * 
 * @param d New thickness
 * @throws OptiSimError if d is non-positive
 */
void ThickLens::setD(double d){
    if(d <= 0) throw OptiSimError("ERROR: \tThe thickness of the lens must be a positive number.");
    if(this->d != d){
        this->d = d;
        this->f = computeF(n, d, r_left, r_right);
    }
}

/**
 * @brief Gets the left radius of curvature.
 * @return The left radius of curvature
 */
double ThickLens::getR_Left(){
    return r_left;
}

/**
 * @brief Sets the left radius of curvature and updates focal length.
 * 
 * @param r_left New left radius
 */
void ThickLens::setR_Left(double r_left){
    if(this->r_left != r_left){
        this->r_left = r_left;
        this->f = computeF(n, d, r_left, r_right);
    }
}

/**
 * @brief Gets the right radius of curvature.
 * @return The right radius of curvature
 */
double ThickLens::getR_Right(){
    return r_right;
}

/**
 * @brief Sets the right radius of curvature and updates focal length.
 * 
 * @param r_right New right radius
 */
void ThickLens::setR_Right(double r_right){
    if(this->r_right != r_right){
        this->r_right = r_right;
        this->f = computeF(n, d, r_left, r_right);
    }
}

/**
 * @brief Calculates the image formed by the thick lens for a given object.
 * 
 * @param is ImagingSubject representing the object to image
 * @return Image representing the result of the lens imaging
 */
Image ThickLens::Calculate(ImagingSubject is){
    double H_left = computeHLeft();
    double H_right = computeHRight();

    double d_is;
    if (isinf(is.getX())) {
        d_is = numeric_limits<double>::infinity();
    } else {
        d_is = H_left - is.getX();
    }
    
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

    return Image(H_right + d_im, y_im, is_real);
}
