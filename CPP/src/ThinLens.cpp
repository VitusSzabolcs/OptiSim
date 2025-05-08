#include "ThinLens.h"
#include <math.h>

ThinLens::ThinLens(double x, double y, double f):Lens(x, y, f){}
Image ThinLens::Calculate(ImagingSubject is){
    double x_is = is.getX();
    double y_is = is.getY();

    double x_im = pow(1/getF() - 1/x_is, -1);
    double y_im = -x_im/x_is*y_is;

    return Image(x_im, y_im, x_im > 0);
}