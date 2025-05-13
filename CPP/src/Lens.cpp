#include "Lens.h"

Lens::Lens(double x, double y, double f):OpticalObject(x, y){
    this->f = f;
}

double Lens::getF(){
    return f;
}