#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include "ThinLens.h"
#include "ThickLens.h"
#include "Image.h"
#include "LightSource.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class OpticalSystem{ 
    private:
        LightSource *LS;
        vector<Image> imageSequence;
    	map<string, OpticalObject*> name_lens_map;
    	vector<string> order;
        vector<ThinLens> thin_lenses;
        vector<ThickLens> thick_lenses;
    public:
		OpticalSystem();
    	OpticalSystem(string);

    	void add(OpticalObject&, string);
    	void add(LightSource);
    	void modifyLightSource(string, double);
    	void modifyOpticalObject(string, string, double);
        void toString();

    	void save(string);
		vector<Image> getImageSequence();
    	Image Calculate();
		~OpticalSystem();
};


#endif