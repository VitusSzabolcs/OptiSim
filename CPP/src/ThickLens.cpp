#include "ThickLens.h"
#include <math.h>

double ThickLens::computeF(double n, double d, double r_left, double r_right){
    double finv = (n-1) * (1/r_left - 1/r_right + (n-1)*d/(n*r_left*r_right));
    return 1/finv;
}

double ThickLens::computeHLeft(){
    return - getF() * (n - 1) * d / r_right / n + getX() - d/2;
}

double ThickLens::computeHRight(){
    return - getF() * (n - 1) * d / r_left / n + getX() + d/2;
}

ThickLens::ThickLens(double x, double y, double n, double d, double r_left, double r_right):Lens(x, y, computeF(n, d, r_left, r_right)){
    this->n = n;
    this->d = d;
    this->r_left = r_left;
    this->r_right = r_right;
}

double ThickLens::getN(){
    return n;
}

void ThickLens::setN(double n){
    if(this->n != n){
        this->n = n;
        this->setF(computeF(n, d, r_right, r_left));
    }
}

double ThickLens::getD(){
    return d;
}

void ThickLens::setD(double d){
    if(this->d != d){
        this->d = d;
        this->setF(computeF(n, d, r_right, r_left));
    }
}

double ThickLens::getR_Left(){
    return r_left;
}

void ThickLens::setR_Left(double r_left){
    if(this->r_left != r_left){
        this->r_left = r_left;
        this->setF(computeF(n, d, r_right, r_left));
    }
}

double ThickLens::getR_Right(){
    return r_right;
}

void ThickLens::setR_Right(double r_right){
    if(this->r_right != r_right){
        this->r_right = r_right;
        this->setF(computeF(n, d, r_right, r_left));
    }
}

Image ThickLens::Calculate(ImagingSubject is){
    double H_left = computeHLeft();
    double H_right = computeHRight();

    double d_is = H_left - is.getX();
    double y_is = is.getY();

    double d_im = pow(1/getF() - 1/d_is, -1);
    double y_im = -d_im/d_is*y_is;

    return Image(H_right + d_im, y_im, d_im > 0);
}