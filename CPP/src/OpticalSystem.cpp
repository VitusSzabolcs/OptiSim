#include "OpticalSystem.h"

OpticalSystem::OpticalSystem() = default;

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

OpticalSystem::~OpticalSystem(){
	delete LS;
	delete IMG;
}