#pragma once

class GameObject;
class Physics {
public:
	~Physics();
	static double getGravitationalConstant() { return G; }
	static void gravitateTowards(GameObject & object1, GameObject & object2);
private:
	const static double G;
};
