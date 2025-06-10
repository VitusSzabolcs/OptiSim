
#include <iostream>  // For standard input/output operations (cout, cerr)
#include <vector>    // For using std::vector
#include <iomanip>   // For formatting output (setw, setprecision)
#include "OptiSim.h" // Main header for the OptiSim library components

using namespace std;


void test_LightSource(){
    cout << "\n\nTesting \e[1mLightSource:\e[0m\n\n";
    LightSource LS = LightSource(10,5);

    if (LS.getX()==10) cout << "\tLightSource -> getX() : works properly (same for Image)\n";
    else cout << "\tLightSource -> getX() : works faulty (same for Image)\n";
    if (LS.getY()==5) cout << "\tLightSource -> getY() : works properly (same for Image)\n";
    else cout << "\tLightSource -> getY() : works faulty (same for Image)\n";
    
    LS.setX(15);
    LS.setY(10);

    if (LS.getX()==15) cout << "\tLightSource -> setX(double) : works properly (same for Image)\n";
    else cout << "\tLightSource -> setX(double) : works faulty (same for Image)\n";
    if (LS.getY()==10) cout << "\tLightSource -> setY(double) : works properly (same for Image)\n";
    else cout << "\tLightSource -> setY(double) : works faulty (same for Image)\n";
}

void test_ThinLens(){
    cout << "\n\nTesting \e[1mThinLens:\e[0m\n\n";
    ThinLens ThinL = ThinLens(10,5);

    if (ThinL.getX()==10) cout << "\tThinLens -> getX() : works properly\n";
    else cout << "\tThinLens -> getX() : works faulty\n";
    if (ThinL.getF()==5) cout << "\tThinLens -> getF() : works properly\n";
    else cout << "\tThinLens -> getF() : works faulty\n";
    
    ThinL.setX(15);
    ThinL.setF(10);

    if (ThinL.getX()==15) cout << "\tThinLens -> setX(double) : works properly\n";
    else cout << "\tThinLens -> setX(double) : works faulty\n";
    if (ThinL.getF()==10) cout << "\tThinLens -> setF(double) : works properly\n";
    else cout << "\tThinLens -> setF(double) : works faulty\n";
    

}

void test_ThickLens(){
    cout << "\n\nTesting \e[1mThickLens:\e[0m\n\n";
    ThickLens ThickL = ThickLens(10, 1.5, 5, -20, 25);

    if (ThickL.getX()==10) cout << "\tThickLens -> getX() : works properly\n";
    else cout << "\tThickLens -> getX() : works faulty\n";
    if (ThickL.getN()==1.5) cout << "\tThickLens -> getN() : works properly\n";
    else cout << "\tThickLens -> getN() : works faulty\n";
    if (ThickL.getD()==5) cout << "\tThickLens -> getD() : works properly\n";
    else cout << "\tThickLens -> getD() : works faulty\n";
    if (ThickL.getR_Left()==-20) cout << "\tThickLens -> getR_Left() : works properly\n";
    else cout << "\tThickLens -> getR_Left() : works faulty\n";
    if (ThickL.getR_Right()==25) cout << "\tThickLens -> getR_Right() : works properly\n";
    else cout << "\tThickLens -> getR_Right() : works faulty\n";
    
    
    ThickL.setX(20);
    ThickL.setN(1.7);
    ThickL.setD(3);
    ThickL.setR_Left(15);
    ThickL.setR_Right(10);

    if (ThickL.getX()==20) cout << "\tThickLens -> setX(double) : works properly\n";
    else cout << "\tThickLens -> setX(double) : works faulty\n";
    if (ThickL.getN()==1.7) cout << "\tThickLens -> setN(double) : works properly\n";
    else cout << "\tThickLens -> setN(double) : works faulty\n";
    if (ThickL.getD()==3) cout << "\tThickLens -> setD(double) : works properly\n";
    else cout << "\tThickLens -> setD(double) : works faulty\n";
    if (ThickL.getR_Left()==15) cout << "\tThickLens -> setR_Left(double) : works properly\n";
    else cout << "\tThickLens -> setR_Left(double) : works faulty\n";
    if (ThickL.getR_Right()==10) cout << "\tThickLens -> setR_Right(double) : works properly\n";
    else cout << "\tThickLens -> setR_Right(double) : works faulty\n";

    ThickL.setN(1.5);
    ThickL.setD(3);
    ThickL.setR_Left(10);
    ThickL.setR_Right(10);

    if (ThickL.getF()==200) cout << "\tThickLens -> getF() : works properly\n";
    else cout << "\tThickLens -> getF() : works faulty\n";
}

void test_OpticalSystem(){
    cout << "\n\nTesting \e[1mOpticalSystem:\e[0m\n\n";
    // Create OpticalSystem and OpticalObjects
    OpticalSystem OS = OpticalSystem();
    LightSource LS = LightSource(0,5);
    ThinLens ThinL = ThinLens(10,5);
    ThickLens ThickL = ThickLens(30, 1.5, 5, -20, 25);

    // Add LightSource to the OpticalSystem & get LightSource from OpticalSystem & check identity
    OS.add(LS);
    LightSource LS_get = OS.getLightSource();
    if (LS_get.getX() == LS.getX() && LS_get.getY() == LS.getY())
        cout << "\tOpticalSystem -> add(LightSource) & getLightSource() : works properly\n";
    else cout << "\tOpticalSystem -> add(LightSource) || getLightSource() : works faulty\n";


    // Add Lenses to the OpticalSystem & get Lenses from OpticalSystem & check identity
    OS.add(ThinL, "Lens1");
    OS.add(ThickL, "Lens2");
    map<string, OpticalObject*> OOList = OS.getSystemElements();
    ThinLens* ThinL_get = (ThinLens*) OOList["Lens1"];
    ThickLens* ThickL_get = (ThickLens*) OOList["Lens2"];

    if (ThinL_get->getX() == ThinL.getX() && ThinL_get->getF() == ThinL.getF() &&
        ThickL_get->getX() == ThickL.getX() && ThickL_get->getN() == ThickL.getN() &&
        ThickL_get->getD() == ThickL.getD() && ThickL_get->getR_Left() == ThickL.getR_Left() &&
        ThickL_get->getR_Right() == ThickL.getR_Right())
        cout << "\tOpticalSystem -> add(OpticalObject&, string) & getSystemElements() : works properly\n";
    else cout << "\tOpticalSystem -> add(OpticalObject&, string) || getSystemElements() : works faulty\n";

    // Modify LightSource & get LightSource from OpticalSystem & check whether the modification was successful
    OS.modifyLightSource("x",-20);
    OS.modifyLightSource("y",10);
    LS_get = OS.getLightSource();
    if (LS_get.getX() == -20 && LS_get.getY() == 10)
        cout << "\tOpticalSystem -> modifyLightSource(string, double) : works properly\n";
    else cout << "\tOpticalSystem -> modifyLightSource(string, double) : works faulty\n";

    // Modify Lenses & get Lenses from OpticalSystem & check whether the modification was successful
    OS.modifyOpticalObject("Lens1", "x", 0);
    OS.modifyOpticalObject("Lens1", "f", 10);
    OS.modifyOpticalObject("Lens2", "x", 30);
    OS.modifyOpticalObject("Lens2", "n", 1.7);
    OS.modifyOpticalObject("Lens2", "d", 3);
    OS.modifyOpticalObject("Lens2", "r_left", 35);
    OS.modifyOpticalObject("Lens2", "r_right", 40);

    OOList = OS.getSystemElements();
    ThinL_get = (ThinLens*) OOList["Lens1"];
    ThickL_get = (ThickLens*) OOList["Lens2"];

    if (ThinL_get->getX() == 0 && ThinL_get->getF() == 10 &&
        ThickL_get->getX() == 30 && ThickL_get->getN() == 1.7 &&
        ThickL_get->getD() == 3 && ThickL_get->getR_Left() == 35 &&
        ThickL_get->getR_Right() == 40)
        cout << "\tOpticalSystem -> modifyOpticalObject(string, string, double) : works properly\n";
    else cout << "\tOpticalSystem -> modifyOpticalObject(string, string, double) : works faulty\n";

    // Remove Lens & get Lenses from OpticalSystem & check whether the remove was successful
    OS.remove("Lens2");
    OOList = OS.getSystemElements();
    ThinL_get = (ThinLens*) OOList["Lens1"];

    if (ThinL_get->getX() == 0 && ThinL_get->getF() == 10 &&
        OOList.size() == 1) // check if we still have Lens1 & if we have only one lens
        cout << "\tOpticalSystem -> remove(string) : works properly\n";
    else cout << "\tOpticalSystem -> remove(string) : works faulty\n";

    // Calculate image formation & get image sequence & check for proper image formation
    OS.Calculate();
    vector<Image> IS =  OS.getImageSequence();
    Image FinalI = IS.back();

    if (FinalI.getX() == 20 && FinalI.getY() == -10 && FinalI.getReal() == 1)
        cout << "\tOpticalSystem -> Calculate() &  getImageSequence(): works properly\n";
    else cout << "\tOpticalSystem -> Calculate() &  getImageSequence() : works faulty\n";

    // Get rays & check if they are correct
    map<string, ray> Rays =  OS.getRays();
    if (Rays["ray_1"].x[0] == -20 && Rays["ray_1"].x[1] == 0 && Rays["ray_1"].x[2] == 20 &&
        Rays["ray_1"].y[0] == 10 && Rays["ray_1"].y[1] == 10 && Rays["ray_1"].y[2] == -10 &&
        Rays["ray_2"].x[0] == -20 && Rays["ray_2"].x[1] == 0 && Rays["ray_2"].x[2] == 20 &&
        Rays["ray_2"].y[0] == 10 && Rays["ray_2"].y[1] == 0 && Rays["ray_2"].y[2] == -10 )
        cout << "\tOpticalSystem -> getRays(): works properly\n";
    else cout << "\tOpticalSystem -> getRays() : works faulty\n";

    // Save the OpticalSystem into file & relaod it from file & check if we get the same OpticalSystem
    OS.save("saved_system.json");
    OpticalSystem OS2 = OpticalSystem("saved_system.json");

    LS_get = OS.getLightSource();
    OOList = OS.getSystemElements();
    ThinL_get = (ThinLens*) OOList["Lens1"];

    if (LS_get.getX() == -20 && LS_get.getY() == 10 &&
        ThinL_get->getX() == 0 && ThinL_get->getF() == 10)
        cout << "\tOpticalSystem -> save(string) & OpticalSystem(string) : works properly\n";
    else cout << "\tOpticalSystem -> save(string) & OpticalSystem(string) : works faulty\n";
}



int main(int argc, char* argv[]){
    try{
        test_LightSource();
        test_ThinLens();
        test_ThickLens();
        test_OpticalSystem();
        
    }catch(exception& e) // Catch any standard exception or custom OptiSimError
    {
        cout << e.what() << "\n";
    }
    return 0;  // Indicate successful execution
}