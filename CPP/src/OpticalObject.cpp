#include "OpticalObject.h"
using namespace std;

OpticalObject::OpticalObject(double x){
    this->x = x;
}

double OpticalObject::getX(){
    return x; 
}


void OpticalObject::setX(double x){
    this->x = x;
}
