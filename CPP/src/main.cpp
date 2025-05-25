#include <iostream>
#include "OpticalSystem.h"
#include <vector>


using namespace std;

int main(){
    try{
        // instantiate lenses and light source
        ThinLens lens1(60, 30);
        ThinLens lens2(90, 30);
        LightSource ls(0, 8);

        // instantiate an optical system and add components ot it
        OpticalSystem my_system;
        my_system.add(lens1, "L1");
        my_system.add(lens2, "L2");
        lens1 = ThinLens(1, 2);
        my_system.add(lens1, "L3");

        my_system.add(ls);

        // print the sistem into the console
        my_system.toString();

        // calculate the system's imaging and save the intermediate and final images as vectors
        Image img = my_system.Calculate();
        vector<Image> myimageSequence = my_system.getImageSequence();

        // print the properties of all the images
        vector<Image>::iterator it;
        for(it = myimageSequence.begin(); it < myimageSequence.end(); it++){
            cout<<(*it).getX()<<" "<<(*it).getY()<<" "<<(*it).getReal() << endl;
        }
        int x = 1;
        if(typeid(lens1).name() == "ThinLens") cout << "megy";


        // instantiate an Optical System object using a .json file
        OpticalSystem my_second_system("../json_files/input.json");
        
        // calculate the system's imaging and print the system into the console
        Image final_image = my_second_system.Calculate();
        my_second_system.toString();

        // modify the system than save it into a new json file
        //my_second_system.add(lens2, "new");
        //my_second_system.save("../json_files/save_after_modification.json");

        // save the intermediate and final images as vectors, than print their properties
        //vector<Image> imageSequence2 = my_second_system.getImageSequence();
        //vector<Image>::iterator it2;
        //for(it2 = imageSequence2.begin(); it2 < imageSequence2.end(); it2++){
        //    cout<<(*it2).getX()<<" "<<(*it2).getY()<<" "<<(*it2).getReal() << endl;
        //}

        // instantiate an Optical System object using the recently created json file, than print it
        OpticalSystem my_third_system("../json_files/save_after_modification.json");
        my_third_system.toString();

        // try to instantiate an Optical System object using a wrong json file
        //OpticalSystem my_fourth_system("../json_files/fake.json");
    }catch(const string& error){
        cout<<error<<endl;
    }

    
    return 0;
}