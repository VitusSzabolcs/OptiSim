#ifndef THINLENS_H
#define THINLENS_H

#include "Lens.h"

class ThinLens: public Lens{
    public:
        ThinLens(double, double, double);
        Image Calculate(ImagingSubject) override;
};

#endif