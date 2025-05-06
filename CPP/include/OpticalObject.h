#ifndef OPTICALOBJECT_H
#define OPTICALOBJECT_H

#include "Image.h"
#include "ImagingSubject.h"
#include "LightSource.h"

class OpticalObject{

    private:
        double x, y;

    protected:
        OpticalObject(double, double);
        
    public:
        double getX();
        double getY();
        void setX(double);
        void setY(double);
        virtual Image Calculate(ImagingSubject) = 0;
};

#endif
