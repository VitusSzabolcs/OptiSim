#include <iostream>
#include "OptiSim.h"

using namespace std;

int main(){
    //create new empty system
    OpticalSystem my_system;

    //create new LightSource at x = 0 and height = 8
    LightSource LS(0, 8);

    //add light source to system
    my_system.add(LS);

    //create new thin lens at x = 20 with f = 10
    ThinLens L1(20, 10);

    //add Light thin lens to system
    my_system.add(L1, "Lens_1");

    //calculate image formation
    my_system.Calculate();

    //print informations about system and image formation
    my_system.toString();

    // ------------------------------------------------------------------------
    //create new system from jason
    OpticalSystem my_second_system("./json_files/presentation2.json");

    //calculate image formation
    my_second_system.Calculate();

    //print informations about system and image formation
    my_second_system.toString();

    //remove a lens
    my_second_system.remove("Lens_1");

    //recalculate image formation
    my_second_system.Calculate();

    //pritn information about system and image formation
    my_second_system.toString();

    //saved modified system
    my_second_system.save("./json_files/presentaion2_modified.json");

    
    return 0;
}