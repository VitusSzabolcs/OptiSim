#include <iostream>
#include "OpticalSystem.h"
#include <vector>


using namespace std;

int main(){
    try{
        ThinLens lens1(60, 30);
        ThinLens lens2(90, 30);
        LightSource ls(0, 8);

        OpticalSystem my_system;
        my_system.add(lens1, "L1");
        my_system.add(lens2, "L2");
        lens1 = ThinLens(1, 2);
        my_system.add(lens1, "L3");

        my_system.add(ls);

        Image img = my_system.Calculate();
        vector<Image> imageSequence = my_system.getImageSequence();

        vector<Image>::iterator it;
        for(it = imageSequence.begin(); it < imageSequence.end(); it++){
            cout<<(*it).getX()<<" "<<(*it).getY()<<" "<<(*it).getReal() << endl;
        }
        int x = 1;
        if(typeid(lens1).name() == "ThinLens") cout << "megy";

    }catch(const string& error){
        cout<<error<<endl;
    }

    
    return 0;
}