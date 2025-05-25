#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "ImagingSubject.h"

class LightSource:public ImagingSubject{
    public:
        LightSource(double, double);
};

#endif