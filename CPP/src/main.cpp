#include <iostream>
#include "OpticalSystem.h"
#include <vector>


using namespace std;

int main(){
    ThinLens lens1(60, 30);
    ThinLens lens2(90, 30);
    LightSource ls(0, 8);

    OpticalSystem my_system;
    my_system.add(lens1, "L1");
    my_system.add(lens2, "L2");

    my_system.add(ls);

    Image img = my_system.Calculate();

    vector<Image> imageSequence = my_system.getImageSequence();

    vector<Image>::iterator it;
    for(it = imageSequence.begin(); it < imageSequence.end(); it++){
        cout<<(*it).getX()<<" "<<(*it).getY()<<" "<<(*it).getReal() << endl;
    }

    cout<<img.getX()<<" "<<img.getY()<<" "<<img.getReal();
    return 0;
}