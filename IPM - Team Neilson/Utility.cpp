#include "Utility.h"

int Utility::uIdCounter = 0;

Utility::Utility() { 
	uID = getNewID(); 
}

Utility::~Utility() {
}

int Utility::getUtilityID() { 
	return uID; 
}

int Utility::getNewID() { 
	return ++uIdCounter; 
}