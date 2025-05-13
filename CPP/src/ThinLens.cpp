#include "ThinLens.h"
#include <math.h>

ThinLens::ThinLens(double x, double y, double f):Lens(x, y, f){}
Image ThinLens::Calculate(ImagingSubject is){
    double d_is = getX() - is.getX();
    double y_is = is.getY();

    double d_im = pow(1/getF() - 1/d_is, -1);
    double y_im = -d_im/d_is*y_is;

    return Image(getX() + d_im, y_im, d_im > 0);
}

void ThinLens::setF(double f){
    this->f = f;
}