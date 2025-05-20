#ifndef OPTICALOBJECT_H
#define OPTICALOBJECT_H

#include "Image.h"
#include "ImagingSubject.h"
#include "LightSource.h"

class OpticalObject{

    protected:
        OpticalObject(double);
        double x;
        
    public:
        double getX();
        void setX(double);
        virtual Image Calculate(ImagingSubject) = 0;
};

#endif
