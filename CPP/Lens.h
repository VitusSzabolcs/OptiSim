#include "OpticalObject.h"

class Lens: public OpticalObject{
    private:
        double f;
    public:
        Lens(double, double, double);
        double getF();
        void setF(double);
};