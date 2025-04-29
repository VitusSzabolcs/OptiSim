#include <iostream>
using namespace std;

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
};
