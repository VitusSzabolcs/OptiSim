#include <iostream>
#include "ThinLens.h"
#include "ThickLens.h"
#include "Image.h"
#include "LightSource.h"

using namespace std;

int main(){
    
    ThinLens lens1(10, 5, 10);
    ThickLens lens2(1, 2, 3, 4, 5, 6);

    cout<<lens1.getX()<<" "<<lens1.getY()<<" "<<lens1.getF()<<endl;
    cout<<lens2.getX()<<" "<<lens2.getY()<<" "<<lens2.getF() << " " << lens2.getN()<<endl;

    Image image(11, 12, true);
    LightSource lightSource(13, 14);

    cout<<image.getX()<<" "<<image.getY()<<" "<<image.getReal()<<endl;
    cout<<lightSource.getX()<<" "<<lightSource.getY()<<endl;

    return 0;
}