#ifndef THICKLENS_H
#define THICKLENS_H

#include "Lens.h"

class ThickLens: public Lens{
    private:
        double n;
        double r_left;
        double r_right;
        double d;
        double computeF(double, double, double, double);
    
    public:
        ThickLens(double, double, double, double, double, double);
        double getN();
        void setN(double);
        double getR_Left();
        void setR_Left(double);
        double getR_Right();
        void setR_Right(double);
        double getD();
        void setD(double);
};

#endif