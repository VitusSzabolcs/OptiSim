#include "OpticalSystem.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <cmath>
#include "OptiSimError.h"


using namespace std;
using json = nlohmann::json;


// Constructors ---------------------------------------------------------------
OpticalSystem::OpticalSystem(){
	LS = nullptr;
};

OpticalSystem::OpticalSystem(string file_name){
	// Read datafrom .json file
    ifstream file(file_name);
    
    if (!file.is_open()) throw OptiSimError("ERROR: \t Failed to open file: "+file_name);

    json data;
    try {
        file >> data;
    } catch (json::parse_error& e) {
		throw OptiSimError("ERROR: \tJSON parse error: " + string(e.what()));
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
            ThickLens thickl = ThickLens(lens["position"],
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
	if(name_lens_map.find(OO_name) != name_lens_map.end()) throw OptiSimError("ERROR: \tThe key is taken, please chose another.");
	if(LS != nullptr){
		if(abs(OO_object.getX() - LS->getX()) < 0.001)throw OptiSimError("ERROR: \tThe Light Source and the Optical Object are too close together. The minimum distance must be at least 0.001 mm");
	}
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

	if(index > 0){
		if(abs(name_lens_map[order[index-1]]->getX() - OO_object.getX()) < 0.001){
			delete name_lens_map[OO_name];
			name_lens_map.erase(OO_name);
			throw OptiSimError("ERROR: \tLenses are too close together. The minimum distance must be at least 0.001 mm");
		}
			
	}
	if (index < order.size()) {
		if (abs(name_lens_map[order[index]]->getX() - OO_object.getX()) < 0.001){
			delete name_lens_map[OO_name];
			name_lens_map.erase(OO_name);
			throw OptiSimError("ERROR: \tLenses are too close together. The minimum distance must be at least 0.001 mm");
		}
			
	}

	order.insert(order.begin() + index, OO_name);
}

void OpticalSystem::add(LightSource ls){
	int size = order.size();
	if(size != 0){
		for(int i = 0; i < size; i++){
			if(abs(name_lens_map[order[i]]->getX() - ls.getX()) < 0.001) throw OptiSimError("ERROR: \tThe Light Source and the " + order[i] + 
			"are too close together. The minimum distance must be at least 0.001 mm");
		}
	}
	LS = new LightSource(ls.getX(), ls.getY());
}


// Modifying methods ----------------------------------------------------------
void OpticalSystem::modifyLightSource(string param, double val){
	if(LS == nullptr) throw OptiSimError("ERROR: \tYou have to add a Light Source to the system before you can modify it");
	if(param == "x"){
		int size = order.size();
		if(size != 0){
			for(int i = 0; i < size; i++){
				if(abs(name_lens_map[order[i]]->getX() - val) < 0.001) throw OptiSimError("ERROR: \tThe Light Source and the " + order[i] + 
				"are too close together. The minimum distance must be at least 0.001 mm");
			}
		}
		LS->setX(val);
	}
	else if(param == "y") LS->setY(val);
	else throw OptiSimError("ERROR: \tInvalid parameter: " + param);
}



// Other methods --------------------------------------------------------------
vector<Image> OpticalSystem::getImageSequence(){
	return imageSequence;
}

Image OpticalSystem::Calculate(){
	if(LS == nullptr) throw OptiSimError("ERROR: \tYou have to add a Light Source to the system before calling the Calculate() method.");
	if(order.size() == 0) throw OptiSimError("ERROR: \tYou have to add Optical Objects to the system first before calling the Calculate() method.");
	
	ray_coord["ray_1"].x = vector<double>();
	ray_coord["ray_2"].x = vector<double>();

	// calculate first image
	imageSequence.clear();

	int start = 0;
	while (start < order.size()) {
		if (LS->getX() > name_lens_map[order[start]]->getX())
        	start++;
    	else
        	break;
	}

	if(start == order.size()) throw OptiSimError("ERROR: \t The Light Source is behind all the Optical Objects, nothing to calculate.");

	// initial coordinates
	ray_coord["ray_1"].x.push_back(LS->getX());
	ray_coord["ray_1"].y.push_back(LS->getY());
	ray_coord["ray_2"].x.push_back(LS->getX());
	ray_coord["ray_2"].y.push_back(LS->getY());

	// first lens
	ray_coord["ray_1"].x.push_back(name_lens_map[order[start]]->getX());
	ray_coord["ray_1"].y.push_back(LS->getY());
	ray_coord["ray_2"].x.push_back(name_lens_map[order[start]]->getX());
	ray_coord["ray_2"].y.push_back(0);

	Image img = name_lens_map[order[start]]->Calculate(*LS);
	
	imageSequence.push_back(img);
	
	for(int i = start+1; i < order.size(); i++){

		NextRayCoords(name_lens_map[order[i]], img, "ray_1");
		NextRayCoords(name_lens_map[order[i]], img, "ray_2");

		img = name_lens_map[order[i]]->Calculate(img);
		imageSequence.push_back(img);
	}
	// rays intersect at final image
	ray_coord["ray_1"].x.push_back(img.getX());
	ray_coord["ray_1"].y.push_back(img.getY());
	ray_coord["ray_2"].x.push_back(img.getX());
	ray_coord["ray_2"].y.push_back(img.getY());
	
	return img;
}
	
void OpticalSystem::toString(ostream& os){

	os << "\n-------------------------------------------------------------------------------\n";
	os << "#    SYSTEM SUMMARY";
	os << "\n-------------------------------------------------------------------------------\n";
	if(LS != nullptr){
		os << "Object Position: " << LS->getX() << ", Size: " << LS->getY() << "\n";

	}
	for (int i=0; i< order.size(); i++){
		ThinLens* ptr_thin = dynamic_cast<ThinLens*>(name_lens_map[order[i]]);
		ThickLens* ptr_thick = dynamic_cast<ThickLens*>(name_lens_map[order[i]]);
		if (ptr_thin){
			os << "\nThin Lens: " << order[i]
				 <<",  Position: " << ptr_thin->getX()
		         << ", Focal Length: " << ptr_thin->getF() << "\n";
		}
		if (ptr_thick){
			os << "\nThick Lens: " << order[i]
				 << ", Position: " << ptr_thick->getX()
	             << ", n: " << ptr_thick->getN()
	             << ", Thickness: " << ptr_thick->getD() 
	        	 << ", Radius_left: " << ptr_thick->getR_Left()
	        	 << ", Radius_right: " << ptr_thick->getR_Right()
				 << ", Focal Length: " << ptr_thick->getF() << "\n";
		}
	}
	if (imageSequence.size() != 0){
		os << "\nImage Position: " << imageSequence.back().getX()
		<< ", Size: " << imageSequence.back().getY()
		<< ", Is real: " << imageSequence.back().getReal();
	}
	os << "\n-------------------------------------------------------------------------------\n";
}

void OpticalSystem::save(string file_name) {
    if (LS == nullptr) throw OptiSimError("ERROR: \tCannot save system: no light source present.");

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
    if (!file.is_open()) throw OptiSimError("ERROR: \tFailed to open file for writing: " + file_name);
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

void OpticalSystem::remove(string name){
	if(name_lens_map.find(name) == name_lens_map.end()) throw OptiSimError("ERROR: \tInvalid key: " + name);
	for(int i = 0; i < order.size(); i++){
		if(order[i] == name) {
			order.erase(order.begin() + i);
			break;
		}
	}
	delete name_lens_map[name];
	name_lens_map.erase(name);
}

void OpticalSystem::modifyOpticalObject(string name, string param, double val){
	if(name_lens_map.find(name) == name_lens_map.end()) throw OptiSimError("ERROR: \tInvalid key: " + name);
	ThinLens* ptr_thin = dynamic_cast<ThinLens*>(name_lens_map[name]);
	ThickLens* ptr_thick = dynamic_cast<ThickLens*>(name_lens_map[name]);
	if (ptr_thin) {
		if(param == "f") ptr_thin->setF(val);
		else if(param == "x"){
			ThinLens l(val, ptr_thin->getF());
			remove(name);
			add(l, name);
		}
		else throw OptiSimError("ERROR: \tInvalid parameter: " + param);
	}
	else if (ptr_thick) {
		if(param == "n") ptr_thick->setN(val);
		else if(param == "r_left") ptr_thick->setR_Left(val);
		else if(param == "r_right") ptr_thick->setR_Right(val);
		else if(param == "d") ptr_thick->setD(val);
		else if(param == "x"){
			ThickLens L(val, ptr_thick->getN(), ptr_thick->getD(), ptr_thick->getR_Left(), ptr_thick->getR_Right());
			remove(name);
			add(L, name);
		}
		else throw OptiSimError("ERROR: \tInvalid parameter: " + param);
	}
}

// Helper method --------------------------------------------------------------
void OpticalSystem::NextRayCoords(OpticalObject* ActualLens, Image ActualImage, string which){
	double x_image = ActualImage.getX();
	double y_image = ActualImage.getY();
	double x_ray = ray_coord[which].x.back();
	double y_ray = ray_coord[which].y.back();
	double x_lens = ActualLens->getX();

	double a = (y_image-y_ray)/(x_image-x_ray);
	double b = y_ray-a*x_ray;
	double x_ray_new = x_lens;
	double y_ray_new = a*x_ray_new+b;

	ray_coord[which].x.push_back(x_ray_new);
	ray_coord[which].y.push_back(y_ray_new);
}

map<string, ray> OpticalSystem::getRays(){
	return ray_coord;
}

map<string, OpticalObject*> OpticalSystem::getSystemElements(){
    std::map<string, OpticalObject*> copyMap;
    for (const auto& [key, objPtr] : name_lens_map) {
		ThinLens* ptr_thin = dynamic_cast<ThinLens*>(objPtr);
		ThickLens* ptr_thick = dynamic_cast<ThickLens*>(objPtr);
        if (ptr_thin) {
            copyMap[key] = new ThinLens(ptr_thin->getX(),ptr_thin->getF());
        }
		else if (ptr_thick) {
	    	copyMap[key] = new ThickLens(ptr_thick->getX(),
	    								 ptr_thick->getN(),
	    								 ptr_thick->getD(),
	    								 ptr_thick->getR_Left(),
	    								 ptr_thick->getR_Right());
    	}
	}
    return copyMap;
}

LightSource OpticalSystem::getLightSource(){
	if (LS == nullptr) throw OptiSimError("ERROR: \tNo light source present.");
	return LightSource(LS->getX(), LS->getY());
}
