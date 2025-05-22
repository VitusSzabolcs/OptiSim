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

        

        my_system.add(ls);

        my_system.toString();

        Image img = my_system.Calculate();
        vector<Image> imageSequence = my_system.getImageSequence();

        vector<Image>::iterator it;
        for(it = imageSequence.begin(); it < imageSequence.end(); it++){
            cout<<(*it).getX()<<" "<<(*it).getY()<<" "<<(*it).getReal() << endl;
        }

        // Instantiating an Optical System object using a .json file
        OpticalSystem my_second_system("../json_files/input.json");
        
        Image final_image = my_second_system.Calculate();
        vector<Image> imageSequence2 = my_second_system.getImageSequence();
        my_second_system.toString();
        vector<Image>::iterator it2;
        for(it2 = imageSequence2.begin(); it2 < imageSequence2.end(); it2++){
            cout<<(*it2).getX()<<" "<<(*it2).getY()<<" "<<(*it2).getReal() << endl;
        }

        OpticalSystem my_third_system("../json_files/input_no_thick.json");
        my_third_system.toString();
    }catch(const string& error){
        cout<<error<<endl;
    }
    return 0;
}