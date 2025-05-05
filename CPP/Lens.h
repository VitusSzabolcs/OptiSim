#ifndef LENS_H
#define LENS_H

#include "OpticalObject.h"

class Lens: public OpticalObject{
    private:
        double f;
    protected:
        Lens(double, double, double);
    public:
        double getF();
        void setF(double);
};

#endif