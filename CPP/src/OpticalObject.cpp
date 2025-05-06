#include "OpticalObject.h"
using namespace std;

OpticalObject::OpticalObject(double x, double y){
    this->x = x;
    this->y = y;
}

double OpticalObject::getX(){
    return x; 
}

double OpticalObject::getY(){
    return y;
}

void OpticalObject::setX(double x){
    this->x = x;
}

void OpticalObject::setY(double y){
    this->y = y;
}