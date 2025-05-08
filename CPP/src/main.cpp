#include <iostream>
#include "ThinLens.h"
#include "ThickLens.h"
#include "Image.h"
#include "LightSource.h"

using namespace std;

int main(){
    
    ThinLens lens(15, 10, 10);
    LightSource ls(0, 2);
    Image im = lens.Calculate(ls);

    cout<<im.getX()<<" "<<im.getY()<<" "<<im.getReal();

    return 0;
}