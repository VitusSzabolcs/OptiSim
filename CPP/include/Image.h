#ifndef IMAGE_H
#define IMAGE_H

#include "ImagingSubject.h"

class Image:public ImagingSubject{
    private:
        bool real;
    public:
        Image(double, double, bool);
        void setReal(bool);
        bool getReal();
};

#endif