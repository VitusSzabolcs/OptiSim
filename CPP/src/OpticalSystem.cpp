/**
* @file OpticalSystem.cpp
* @brief Implements the OpticalSystem class, managing optical elements and simulations.
* @author Bács Tamás <tamas.bacs@stud.ubbcluj.ro>
* @author Vitus Szabolcs <szabolcs.vitus1@stud.ubbcluj.ro>
* @date 2025-06-09
*/

#include "OpticalSystem.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp> // Assumes nlohmann/json library is installed
#include <typeinfo>          // For dynamic_cast type checking
#include <cmath>             // For abs()
#include "OptiSimError.h"    // Custom exception class


using namespace std;
using json = nlohmann::json;


// Constructors ---------------------------------------------------------------
/**
 * @details This default constructor initializes the LightSource pointer to `nullptr`, indicating no light source is currently part of the system.
 */
OpticalSystem::OpticalSystem(){
	LS = nullptr;
};

/**
 * @details This constructor loads the optical system configuration from a specified JSON file.
 * It reads the light source and various lens types (thin or thick) and adds them to the system.
 * @param file_name The path to the JSON configuration file.
 * @throws OptiSimError If the file cannot be opened, or if there's a JSON parsing error.
 */
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

/**
 * @details This method adds an `OpticalObject` (like a `ThinLens` or `ThickLens`) to the system,
 * managing its memory and ensuring it's added in the correct optical order based on its x-position.
 * It also performs checks for duplicate names and minimum distances between objects.
 * @param OO_object A reference to the `OpticalObject` to be added.
 * @param OO_name A unique string identifier for the optical object.
 * @throws OptiSimError If the chosen name is already taken, or if the object is too close to an existing light source or another optical object.
 */
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

/**
 * @details This method adds a `LightSource` to the optical system. If a light source already exists, it is replaced.
 * It checks for minimum distance constraints with existing optical objects.
 * @param ls The `LightSource` object to be added.
 * @throws OptiSimError If the `LightSource` is too close to an existing optical object.
 */
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
/**
 * @details This method modifies a specific property (e.g., x or y coordinate) of the light source.
 * It includes validation to ensure the light source exists and adheres to distance constraints with optical objects.
 * @param param The name of the property to modify (e.g., "x" for x-coordinate, "y" for y-coordinate).
 * @param val The new double value for the specified property.
 * @throws OptiSimError If no `LightSource` is present in the system, if `param` is an invalid property name, or if the new position is too close to an existing optical object.
 */
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

/**
 * @details This method modifies a specific property of an existing optical object (e.g., position, focal length, refractive index).
 * It dynamically casts the object to its specific type to call the correct setter method and handles re-insertion into the `order` vector if the position changes.
 * @param name The string name of the optical object to modify.
 * @param param The name of the property to modify (e.g., "x", "f", "n", "r_left", "r_right", "d").
 * @param val The new double value for the specified property.
 * @throws OptiSimError If the provided `name` does not correspond to an existing optical object, or if `param` is an invalid property name for that object type.
 */
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


// Other methods --------------------------------------------------------------
/**
 * @details This method returns a copy of the sequence of images formed by the optical objects in the system.
 */
vector<Image> OpticalSystem::getImageSequence(){
	return imageSequence;
}

/**
 * @details This method simulates the path of light through the optical system, calculates the image formed by each optical object in sequence, and traces representative rays.
 * It updates the `imageSequence` and `ray_coord` members.
 * @return The final `Image` object formed by the entire optical system.
 * @throws OptiSimError If no `LightSource` is present, if no `OpticalObjects` are in the system, or if the light source is positioned behind all optical objects.
 */
Image OpticalSystem::Calculate(){
	if(LS == nullptr) throw OptiSimError("ERROR: \tYou have to add a Light Source to the system before calling the Calculate() method.");
	if(order.size() == 0) throw OptiSimError("ERROR: \tYou have to add Optical Objects to the system first before calling the Calculate() method.");
	
	ray_coord["ray_1"].x = vector<double>();
	ray_coord["ray_1"].y = vector<double>();
	ray_coord["ray_2"].x = vector<double>();
	ray_coord["ray_2"].y = vector<double>();

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

/**
 * @details This method prints a formatted summary of the optical system, including details of the light source,
 * all optical objects (thin and thick lenses), and the final calculated image (if available).
 * @param os The output stream to which the summary will be written. Defaults to `std::cout`.
 */
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

/**
 * @details This method saves the current configuration of the optical system to a JSON file.
 * It includes details of the light source and all added lenses (thin or thick).
 * @param file_name The path to the file where the system configuration will be saved.
 * @throws OptiSimError If no LightSource is present in the system, or if the file cannot be opened for writing.
 */
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
/**
 * @details This destructor is responsible for cleaning up dynamically allocated memory.
 * It iterates through the `name_lens_map` to `delete` all `OpticalObject` pointers and also `delete`s the `LightSource` pointer.
 */
OpticalSystem::~OpticalSystem(){
	for(int i = 0; i < order.size(); i++){
		delete name_lens_map[order[i]];
	}
	name_lens_map.clear();
	delete LS;
}

/**
 * @details This method removes an optical object from the system by its unique name.
 * It deallocates the memory associated with the object and removes its entry from the internal maps and order vector.
 * @param name The string name of the optical object to be removed.
 * @throws OptiSimError If the provided `name` does not correspond to an existing optical object in the system.
 */
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

/**
 * @details This is a helper method used internally by `Calculate()` to determine the coordinates of a ray as it passes through an optical object.
 * It calculates the point where the ray intersects the plane of the given `ActualLens` based on the previous image formed.
 * @param ActualLens A pointer to the `OpticalObject` (lens) that the ray is currently interacting with.
 * @param ActualImage The `Image` object formed by the *previous* optical element or the initial `LightSource`.
 * @param which A string identifier for the ray being traced (e.g., "ray_1", "ray_2").
 */
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

/**
 * @details This method returns a map containing the traced ray coordinates.
 * The map keys are ray identifiers (e.g., "ray_1", "ray_2"), and the values are `ray` structs holding x and y coordinate sequences.
 * @return A `std::map<std::string, ray>` containing the ray trace data.
 */
map<string, ray> OpticalSystem::getRays(){
	return ray_coord;
}

/**
 * @details This method provides a copy of the map containing all optical elements (lenses) in the system.
 * It performs a deep copy to ensure memory safety for the returned pointers.
 * @return A `std::map<std::string, OpticalObject*>` where keys are object names and values are pointers to copies of the `OpticalObject` instances.
 */
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

/**
 * @details This method retrieves a copy of the `LightSource` currently in the system.
 * @return A `LightSource` object representing the current light source.
 * @throws OptiSimError If no `LightSource` has been added to the system yet.
 */
LightSource OpticalSystem::getLightSource(){
	if (LS == nullptr) throw OptiSimError("ERROR: \tNo light source present.");
	return LightSource(LS->getX(), LS->getY());
}
