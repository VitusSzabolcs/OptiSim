#ifndef LENS_H
#define LENS_H

#include "OpticalObject.h"

class Lens: public OpticalObject{
    protected:
        Lens(double, double);
        double f;
    public:
        double getF();
};

#endif