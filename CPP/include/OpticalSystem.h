
#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include "ThinLens.h"
#include "ThickLens.h"
#include "Image.h"
#include "LightSource.h"
#include <map>
#include <vector>

using namespace std;

class OpticalSystem{ 
    private:
        LightSource *LS;
        Image *IMG;
    	map<string, OpticalObject*> name_lens_map;
    	vector<string> order;
    public:
		OpticalSystem();
    	OpticalSystem(string);
    	void add(OpticalObject&, string);
    	//void add(LightSource);
    	void modifyLightSource(double, double);
    	void modifyOpticalObject(string, string, double);
    	void save(string);
    	Image Calculate();
		~OpticalSystem();
};


#endif