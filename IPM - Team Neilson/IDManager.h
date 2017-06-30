#pragma once
class IDManager
{
public:
	~IDManager() {}
	static int getNewCompID();
private:
	static int compCount;
};
