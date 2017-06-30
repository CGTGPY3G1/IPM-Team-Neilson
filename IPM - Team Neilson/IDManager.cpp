#include "IDManager.h"

int IDManager::compCount = 0;

int IDManager::getNewCompID() { return ++compCount; }
