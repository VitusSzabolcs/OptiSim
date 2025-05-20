#include "Lens.h"

Lens::Lens(double x, double f):OpticalObject(x){
    this->f = f;
}

double Lens::getF(){
    return f;
}