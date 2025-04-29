#include <iostream>
#include "Lens.h"

using namespace std;

int main(){
    Lens lens(1, 2, 3);
    cout <<"F = " << lens.getF() << endl;
    cout <<"X = " << lens.getX() << endl;
    cout <<"Y = " << lens.getY() << endl;
    return 0;
}