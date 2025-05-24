#include "OpticalSystem.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <typeinfo>


using namespace std;
using json = nlohmann::json;


// Constructors ---------------------------------------------------------------
OpticalSystem::OpticalSystem(){
	LS = nullptr;
};

OpticalSystem::OpticalSystem(string file_name){
	// Read datafrom .json file
    ifstream file(file_name);
    
    if (!file.is_open()) throw string("Failed to open file: "+file_name);

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
            ThinLens thinl = ThinLens(lens["position"], lens["focal_length"]);
            add(thinl, lens["name"]);

        } else if (type == "thick") {
            ThickLens thickl =ThickLens(lens["position"],
							  lens["refractive_index"],
							  lens["thickness"],
							  lens["radius_left"],
							  lens["radius_right"]);
            add(thickl, lens["name"]);
        }
    }   
};

// Adding methods -------------------------------------------------------------
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


// Modifying methods ----------------------------------------------------------
void OpticalSystem::modifyLightSource(string param, double val){
	if(LS == nullptr) throw string("You have to add a lightSource to the system before you can modify it");
	if(param == "x") LS->setX(val);
	else if(param == "y") LS->setY(val);
	else throw string("Invalid parameter.");
}



// Other methods --------------------------------------------------------------
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
	
void OpticalSystem::toString(){

	cout << "\n-------------------------------------------------------------------------------\n";
	cout << "#    SYSTEM SUMMARY";
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
				 << ", Position: " << ptr_thick->getX()
	             << ", n: " << ptr_thick->getN()
	             << ", Thickness: " << ptr_thick->getD() 
	        	 << ", Radius_left: " << ptr_thick->getR_Left()
	        	 << ", Radius_right: " << ptr_thick->getR_Right()<< "\n";
		}
	}
	if (imageSequence.size() != 0){
		cout << "\n\e[1mImage Position: " << imageSequence.back().getX()
		<< ", Size: " << imageSequence.back().getY()
		<< ", Is real: " << imageSequence.back().getReal() << "\e[0m";
	}
	cout << "\n-------------------------------------------------------------------------------\n";
}

void OpticalSystem::save(string file_name) {
    if (LS == nullptr) throw string("Cannot save system: no light source present.");

    json data;

    // Save light source (object)
    data["object"] = {
        {"position", LS->getX()},
        {"size", LS->getY()}
    };

    // Save lenses
    for (const auto& name : order) {
        OpticalObject* obj = name_lens_map[name];
        ThinLens* thin = dynamic_cast<ThinLens*>(obj);
        ThickLens* thick = dynamic_cast<ThickLens*>(obj);

        if (thin) {
            data["lenses"].push_back({
                {"name", name},
                {"type", "thin"},
                {"position", thin->getX()},
                {"focal_length", thin->getF()}
            });
        } else if (thick) {
            data["lenses"].push_back({
                {"name", name},
                {"type", "thick"},
                {"position", thick->getX()},
                {"radius_left", thick->getR_Left()},
                {"radius_right", thick->getR_Right()},
                {"refractive_index", thick->getN()},
                {"thickness", thick->getD()}
            });
        }
    }

    // Write to file
    ofstream file(file_name);
    if (!file.is_open()) throw string("Failed to open file for writing: " + file_name);
    file << std::setw(2) << data << std::endl;  // Pretty-print with indentation
    file.close();
}


// Destructor -----------------------------------------------------------------
OpticalSystem::~OpticalSystem(){
	for(int i = 0; i < order.size(); i++){
		delete name_lens_map[order[i]];
	}
	name_lens_map.clear();
	delete LS;
}