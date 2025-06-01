#include "Lens.h"
#include <iostream>
#include "OptiSimError.h"

using namespace std;

Lens::Lens(double x, double f):OpticalObject(x){
    if (f == 0) throw OptiSimError("ERROR: \tFocal length cannot be zero.");
    this->f = f;
}

double Lens::getF(){
    return f;
}