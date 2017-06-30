#include "MyMath.h"

#include "Transform.h"
#include <iomanip>

double MyMath::pi() {
	return 3.1415927;
}

double MyMath::tau() {
	return 6.2831853;
}

double MyMath::radiansToDegrees() {
	return 180.0 / pi();
}

double MyMath::degreesToRadians() {
	return pi() / 180.0;
}


