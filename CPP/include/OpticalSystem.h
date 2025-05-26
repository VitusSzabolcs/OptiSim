#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include "ThinLens.h"
#include "ThickLens.h"
#include "Image.h"
#include "LightSource.h"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class OpticalSystem{ 
    private:
        LightSource *LS;
        vector<Image> imageSequence;
    	map<string, OpticalObject*> name_lens_map;
    	vector<string> order;
    public:
        // constructors
		OpticalSystem();
    	OpticalSystem(string);
        // adding methods
    	void add(OpticalObject&, string);
    	void add(LightSource);
		// removing method
		void remove(string);
        // modifying methods
    	void modifyLightSource(string, double);
    	void modifyOpticalObject(string, string, double);
        // other methods
        void toString(ostream& os = cout);
    	void save(string);
		vector<Image> getImageSequence();
    	Image Calculate();
        // destructor
		~OpticalSystem();
};


#endif