#include "OpticalSystem.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <typeinfo>


using namespace std;
using json = nlohmann::json;

OpticalSystem::OpticalSystem(){
	LS = nullptr;
};

OpticalSystem::OpticalSystem(string file_name){
	// Read datafrom .json file
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_name << "\n";
    }

    json data;
    try {
        file >> data;
    } catch (json::parse_error& e) {
        cerr << "JSON parse error: " << e.what() << '\n';
    }

    // Extract information
    // Object info
    LightSource light_source_readout(data["object"]["position"],
    								 data["object"]["size"]);
    add(light_source_readout);
    
    
    for (const auto& lens : data["lenses"]) {
        string type = lens.value("type", "thin");
        

        if (type == "thin") {

        	//thin_lenses.push_back(ThinLens(lens["position"], lens["focal_length"]));
            ThinLens thinl = ThinLens(lens["position"], lens["focal_length"]);
            add(thinl, lens["name"]);

        } else if (type == "thick") {
            //thick_lenses.push_back(ThickLens(lens["position"],
            //							  lens["refractive_index"],
            //							  lens["thickness"],
            //							  lens["radius_left"],
            //							  lens["radius_right"]));

            //add(thick_lenses.back(), lens["name"]);
            ThickLens thickl =ThickLens(lens["position"],
							  lens["refractive_index"],
							  lens["thickness"],
							  lens["radius_left"],
							  lens["radius_right"]);
            add(thickl, lens["name"]);
        }
    }   
};


void OpticalSystem::add(OpticalObject& OO_object, string OO_name){
	if(name_lens_map.find(OO_name) != name_lens_map.end()) throw string("The name is taken, please chose another.");
	ThinLens* ptr_thin = dynamic_cast<ThinLens*>(&OO_object);
	ThickLens* ptr_thick = dynamic_cast<ThickLens*>(&OO_object);

	if (ptr_thin) {
    	name_lens_map[OO_name] = new ThinLens(ptr_thin->getX(),ptr_thin->getF());

	} else if (ptr_thick) {
	    name_lens_map[OO_name] = new ThickLens(ptr_thick->getX(),
	    									   ptr_thick->getN(),
	    									   ptr_thick->getD(),
	    									   ptr_thick->getR_Left(),
	    									   ptr_thick->getR_Right());
	}
	//name_lens_map[OO_name] = &OO_object;
	int size = order.size();

	if (size == 0){
		order.push_back(OO_name);
		return;
	}
	
	int index = size;
	
	for(int i=0; i<size; i++){
		if (name_lens_map[order[i]]->getX() > OO_object.getX()){
			index = i;
			break;
		}
	}

	order.insert(order.begin() + index, OO_name);

}

void OpticalSystem::add(LightSource ls){

	LS = new LightSource(ls.getX(), ls.getY());
}

OpticalSystem::~OpticalSystem(){

	delete LS;
}

vector<Image> OpticalSystem::getImageSequence(){
	return imageSequence;
}

Image OpticalSystem::Calculate(){
	if(LS == nullptr) throw string("You have to add a lightSource to the system before calling the Calculate() method.");
	if(order.size() == 0) throw string("You have to add OpticalObjects to the system first before calling the Calculate() method.");
	
	imageSequence.clear();
	
	Image img = name_lens_map[order[0]]->Calculate(*LS);
	
	imageSequence.push_back(img);
	
	for(int i = 1; i < order.size(); i++){
		
		img = name_lens_map[order[i]]->Calculate(img);
		
		imageSequence.push_back(img);
	}
	return img;
}

void OpticalSystem::modifyLightSource(string param, double val){
	if(LS == nullptr) throw string("You have to add a lightSource to the system before you can modify it");
	if(param == "x") LS->setX(val);
	else if(param == "y") LS->setY(val);
	else throw string("Invalid parameter.");
}
	
void OpticalSystem::toString(){

	cout << "\n-------------------------------------------------------------------------------\n";
	if(LS != nullptr){
		cout << "Object Position: " << LS->getX() << ", Size: " << LS->getY() << "\n";

	}
	for (int i=0; i< order.size(); i++){
		ThinLens* ptr_thin = dynamic_cast<ThinLens*>(name_lens_map[order[i]]);
		ThickLens* ptr_thick = dynamic_cast<ThickLens*>(name_lens_map[order[i]]);
		if (ptr_thin){
			cout << "\nThin Lens: " << order[i]
				 <<",  Position: " << ptr_thin->getX()
		         << ", Focal Length: " << ptr_thin->getF() << "\n";
		}
		if (ptr_thick){
			cout << "\nThick Lens: " << order[i]
				 << "  Position: " << ptr_thick->getX()
	             << ", n: " << ptr_thick->getN()
	             << ", Thickness: " << ptr_thick->getD() 
	        	 << ", Radius_left: " << ptr_thick->getR_Left()
	        	 << ", Radius_right: " << ptr_thick->getR_Right()<< "\n";
		}
	}
	if (imageSequence.size() != 0){
		cout << "\nImage Position: " << imageSequence.back().getX()
		<< ", Size: " << imageSequence.back().getY()
		<< ", Is real: " << imageSequence.back().getReal() << "\n";
	}
	cout << "\n-------------------------------------------------------------------------------\n";
}