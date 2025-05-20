#include "OpticalSystem.h"

OpticalSystem::OpticalSystem(){
	LS = nullptr;
};

void OpticalSystem::add(OpticalObject& OO_object, string OO_name){
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
	LS = &ls;
}

OpticalSystem::~OpticalSystem(){
	delete LS;
}

vector<Image> OpticalSystem::getImageSequence(){
	return imageSequence;
}

Image OpticalSystem::Calculate(){
	imageSequence.clear();
	Image img = name_lens_map[order[0]]->Calculate(*LS);
	imageSequence.push_back(img);
	for(int i = 1; i < order.size(); i++){
		img = name_lens_map[order[i]]->Calculate(img);
		imageSequence.push_back(img);
	}
	return img;
}