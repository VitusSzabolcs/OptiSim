#include "OpticalSystem.h"

OpticalSystem::OpticalSystem(){
}

void OpticalSystem::add(OpticalObject OO_object, string OO_name){

	name_lens_mag[OO_name] = &OO_object;
	if (order.size()==0) order[0] = OO_name;
	else { 
		for(int i=0; i<order.size(); i++){
			if (name_lens_mag[order[i]].getX() > OO_object.getX()){
				order.insert(order.begin() + i, OO_name);
				break;
			}
		}
	}
}