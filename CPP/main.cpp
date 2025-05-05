#include <iostream>
#include "ThinLens.h"
#include "ThickLens.h"

using namespace std;

int main(){
    
    ThinLens lens1(10, 5, 10);
    ThickLens lens2(1, 2, 3, 4, 5, 6);

    cout<<lens1.getX()<<" "<<lens1.getY()<<" "<<lens1.getF()<<endl;
    cout<<lens2.getX()<<" "<<lens2.getY()<<" "<<lens2.getF() << " " << lens2.getN();

    return 0;
}