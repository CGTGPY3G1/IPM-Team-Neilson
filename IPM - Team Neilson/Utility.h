#pragma once

class Utility
{
public:
	Utility();
	~Utility();
	int getUtilityID();
private:
	static int uIdCounter;
	static int getNewID();
	int uID;
};
