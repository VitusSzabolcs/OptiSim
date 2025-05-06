#include "ImagingSubject.h"

ImagingSubject::ImagingSubject(double x, double y){
    this->x = x;
    this->y = y;
}

double ImagingSubject::getX(){
    return x;
}

double ImagingSubject::getY(){
    return y;
}

void ImagingSubject::setX(double x){
    this->x = x;
}

void ImagingSubject::setY(double y){
    this->y = y;
}