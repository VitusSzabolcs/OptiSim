#include "ThickLens.h"

double ThickLens::computeF(double n, double d, double r_left, double r_right){
    double finv = (n-1) * (1/r_left - 1/r_right + (n-1)*d/(n*r_left*r_right));
    return 1/finv;
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
    this->n = n;
}

double ThickLens::getD(){
    return d;
}

void ThickLens::setD(double d){
    this->d = d;
}

double ThickLens::getR_Left(){
    return r_left;
}

void ThickLens::setR_Left(double r_left){
    this->r_left = r_left;
}

double ThickLens::getR_Right(){
    return r_right;
}

void ThickLens::setR_Right(double r_right){
    this->r_right = r_right;
}