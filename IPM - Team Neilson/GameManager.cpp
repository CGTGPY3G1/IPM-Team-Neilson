#include "GameManager.h"
#include "GameObject.h"
#include <algorithm>
GameManager * GameManager::instance = NULL;
GameManager::GameManager() {
}

GameManager::~GameManager() {
	for(std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) {
		delete (*i);
	}
	delete instance;
}

GameManager * GameManager::getInstance() {
	if(!instance)
		instance = new GameManager();
	return instance;
}

void GameManager::start() {
}

void GameManager::update() {
	for(std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) {
		(*i)->update();
	}
}

void GameManager::update(const double & deltaTime) {
	for(std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) {
		(*i)->update(deltaTime);
	}
}

void GameManager::fixedUpdate(const double & FixedDeltaTime) {
	for(std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) {
		(*i)->fixedUpdate(FixedDeltaTime);
	}
}

void GameManager::lateUpdate() {
	for(std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) {
		(*i)->lateUpdate();
	}
}

void GameManager::render() {
	for(std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) {
		(*i)->render();
	}
}

bool compareRenderers(GameObject * a, GameObject * b) {
	if(a->getRenderer() && b->getRenderer())
		return (a->getRenderer()->getSortLayer() < b->getRenderer()->getSortLayer());
	else if(a->getRenderer())
		return true;
	return false;
}

void GameManager::addGameObject(GameObject * toAdd) {	
	gameObjects.push_back(toAdd);
	std::sort(gameObjects.begin(), gameObjects.end(), compareRenderers);
}

void GameManager::removeGameObject(GameObject * toRemove) {
	std::vector<GameObject*>::iterator position = std::find(gameObjects.begin(), gameObjects.end(), toRemove);
	if(position != gameObjects.end()) {
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), toRemove), gameObjects.end());
	}
}

GameObject * GameManager::findByName(const std::string & name) {
	for(std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) {
		if((*i)->getName().compare(name) == 0)
			return (*i);
	}
	return NULL;
}


