#pragma once
#include <vector>
class GameObject;
class GameManager {
public:
	
	~GameManager();
	static GameManager * getInstance();
	void start();
	void update();
	void update(const double & deltaTime);
	void fixedUpdate(const double & FixedDeltaTime);
	void lateUpdate();
	void render();
	void addGameObject(GameObject * toAdd);
	void removeGameObject(GameObject * toRemove);
	GameObject * findByName(const std::string & name);
private:
	GameManager();
	static GameManager * instance;
	std::vector<GameObject*> gameObjects;
};

