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

    cout<<im.getX()<<" "<<im.getY()<<" "<<im.getReal() << endl;

    ThickLens Lens(30 + 0.5, 10, 1.5, 1, 20, -40);
    LightSource Ls(0, 2);
    Image Im = Lens.Calculate(Ls);

    cout<<Im.getX()<<" "<<Im.getY()<<" "<<Im.getReal() << endl;

    return 0;
}