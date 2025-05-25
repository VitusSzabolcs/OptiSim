#include "ThickLens.h"
#include <string>
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;


double ThickLens::computeF(double n, double d, double r_left, double r_right){
    if(r_left == 0.0 || r_right == 0.0) {
        throw string("The radius of the surface cannot be 0.");
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
double ThickLens::computeHLeft(){
    return - f * (n - 1) * d / r_right / n + x - d/2;
}

double ThickLens::computeHRight(){
    return - f * (n - 1) * d / r_left / n + x + d/2;
}

ThickLens::ThickLens(double x, double n, double d, double r_left, double r_right):Lens(x, computeF(n, d, r_left, r_right)){
    if(n <= 0) throw string("The refractive index must be a positive number.");
    if(d <= 0) throw string("The thickness of the lens must be a positive number.");
    this->n = n;
    this->d = d;
    this->r_left = r_left;
    this->r_right = r_right;
}

double ThickLens::getN(){
    return n;
}

void ThickLens::setN(double n){
    if(n <= 0) throw string("The refractive index must be a positive number.");
    if(this->n != n){
        this->n = n;
        this->f = computeF(n, d, r_left, r_right);
    }
}

double ThickLens::getD(){
    return d;
}

void ThickLens::setD(double d){
    
    if(this->d != d){
        this->d = d;
        this->f = computeF(n, d, r_left, r_right);
    }
}

double ThickLens::getR_Left(){
    return r_left;
}

void ThickLens::setR_Left(double r_left){
    if(this->r_left != r_left){
        this->r_left = r_left;
        this->f = computeF(n, d, r_left, r_right);
    }
}

double ThickLens::getR_Right(){
    return r_right;
}

void ThickLens::setR_Right(double r_right){
    if(this->r_right != r_right){
        this->r_right = r_right;
        this->f = computeF(n, d, r_left, r_right);
    }
}

#include <limits>
#include <cmath>

using namespace std;

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