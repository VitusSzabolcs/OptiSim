#include "OpticalSystem.h"
#include <iostream>

using namespace std;

OpticalSystem::OpticalSystem(){
	LS = nullptr;
};

void OpticalSystem::add(OpticalObject& OO_object, string OO_name){
	if(name_lens_map.find(OO_name) != name_lens_map.end()) throw string("The name is taken, please chose another.");
	name_lens_map[OO_name] = &OO_object;
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