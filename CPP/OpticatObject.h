#include <iostream>
using namespace std;

class OpticalObject{

    private:
        double x, y;
    public:
        OpticalObject(double, double);
        double getX();
        double getY();
        void setX(double);
        void setY(double);
        friend ostream& operator<<(ostream&, const OpticalObject&);
};