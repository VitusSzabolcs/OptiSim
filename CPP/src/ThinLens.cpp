#include "ThinLens.h"
#include <cmath>
#include <limits>

using namespace std;

ThinLens::ThinLens(double x, double f):Lens(x, f){}
Image ThinLens::Calculate(ImagingSubject is){
    double d_is = x - is.getX();
    double y_is = is.getY();

    double d_im;
    double y_im;
    bool is_real;

    if (isinf(d_is)) {
        d_im = f;
        y_im = 0.0;
        is_real = (f > 0);
    } else {
        double denominator = d_is - f;

        if (abs(denominator) < numeric_limits<double>::epsilon()) {
            y_im = numeric_limits<double>::infinity();
            if (f > 0) {
                d_im = numeric_limits<double>::infinity();
                is_real = true;
            } else {
                d_im = -numeric_limits<double>::infinity();
                is_real = false;
            }
        } else {
            d_im = (f * d_is) / denominator;
            y_im = -d_im / d_is * y_is;
            is_real = d_im > 0;
        }
    }

    return Image(x + d_im, y_im, is_real);
}

void ThinLens::setF(double f){
    this->f = f;
}