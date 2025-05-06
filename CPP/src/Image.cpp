#include "Image.h"

Image::Image(double x, double y, bool real):ImagingSubject(x, y){
    this->real = real;
}

bool Image::getReal(){
    return real;
}

void Image::setReal(bool real){
    this->real = real;
}