#include<windows.h>
#include<iostream>
#include<gl/glut.h>
#include <vector>
#include"Vector2.h"
#include "Gameobject.h"
#include "Transform.h"
#include "Renderable.h"
#include "Movement.h"
#include "Capsule.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "GameManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Tracker.h"
#include "CollisionManager.h"
#include "Physics.h"
#include <algorithm>
#include <fstream>
using namespace std;
// game update time increment.  Resolution width and height
const double FIXED_TIME_STEP = 0.02, WIDTH = 1280, HEIGHT = 720;
// Current viewport width and height
double newWidth, newHeight;

// time taken for last frame and amount of unprocessed time
double deltaTime = 0, lagTime = 0;
// tracks number of miliseconds since program started
int oldTime = 0;
// true is mouse button 1 is held down
bool mouseDown = false;
// Used to track the mouse position and it's scale relative to the window size
Vector2 mousePosition = Vector2(0, 0), mouseStart = Vector2(0, 0), mouseEnd = Vector2(0, 0), coordAspect = Vector2::One;

// handles updates and rendering 
GameManager * gameManager = GameManager::getInstance();
Camera * camera;
bool paused = false;
// Used for tracking key presses
const unsigned int NO_OF_KEYS = 256;
bool keyStates[NO_OF_KEYS];
bool oldKeyStates[NO_OF_KEYS];

GameObject * largeMass, *tempMass;
vector<GameObject*> smallMasses;

// standard mass for small objects
double mass = 10000.0;
// return true if key is currently pressed
bool getKey(unsigned int key) {
	return key < NO_OF_KEYS ? keyStates[key] : false;
}

// return true if key was not pressed on last but is pressed on this frame
bool getKeyDown(unsigned int key) {
	return key < NO_OF_KEYS ? !oldKeyStates[key] && keyStates[key] : false;
}

// return true if key was pressed on last but is released on this frame
bool getKeyUp(unsigned int key) {	
	return key < NO_OF_KEYS ? oldKeyStates[key] && !keyStates[key] : false;
}

// Update key states
void updateKeys() {
	for(size_t i = 0; i < NO_OF_KEYS; i++) {
		oldKeyStates[i] = keyStates[i];
	}
}

void showDirections() {
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for(size_t i = 0; i < smallMasses.size(); i++) {
		Shape *shape = smallMasses[i]->getComponent<Collider>()->getShape();
		Vector2 direction = smallMasses[i]->getMovement()->getVelocity().normalized();
		Vector2 position = smallMasses[i]->getTransform()->getPosition();
		double radius = shape->getRadius()*0.7;
		glVertex2d(position.x - direction.x * radius, position.y - direction.y * radius);
		Vector2 pointPosition = Vector2(position.x + direction.x * radius, position.y + direction.y * radius);
		glVertex2d(pointPosition.x, pointPosition.y);
		radius *= 0.6;
		glVertex2d(position.x - direction.y * radius, position.y + direction.x * radius);
		glVertex2d(pointPosition.x, pointPosition.y);
		glVertex2d(position.x + direction.y * radius, position.y - direction.x * radius);
		glVertex2d(pointPosition.x, pointPosition.y);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gameManager->render();
	
	showDirections();
	glFlush();
	
}

void fireNewMass() {
	if(mouseDown) {
		// Create and configure a new small mass
		if(!tempMass)
			tempMass = new GameObject(mousePosition, 0, ("SmallMass" + std::to_string((int)smallMasses.size()+1)));
		if(!tempMass->getRenderer()) {
			tempMass->addComponent(GameObject::createComponent<Renderer>());
			Circle *c2 = new Circle(Vector2(0, 0), 20);
			c2->setColour(1, 1, 1, 1);
			tempMass->getRenderer()->addRenderable(c2);
		}
		if(!tempMass->getMovement()) {
			tempMass->addComponent(GameObject::createComponent<Movement>());
			tempMass->getMovement()->setMass(mass);
		}
		if(!tempMass->getComponent<Collider>()) {
			tempMass->addComponent(GameObject::createComponent<Collider>()->setShape(new Circle(Vector2(0, 0), 20))->shouldRender(false));
			//Tracker * tracker = GameObject::createComponent<Tracker>();
			//tracker->setTarget(largeMass->getTransform());
			//tempMass->addComponent(tracker);
		}
	}
	else if(tempMass) {
		// if a new small mass has been created add it 2 the game manager (so it can be rendered) and add it to the small masses array
		if(!CollisionManager::pointInCircle(largeMass->getTransform()->getPosition(), largeMass->getComponent<Collider>()->getShape()->getRadius(), mouseStart)) {
			Vector2 velocity = mouseEnd - mouseStart;
			tempMass->getMovement()->setVelocity(velocity);
			GameObject * newMass = tempMass;
			smallMasses.push_back(newMass);
			gameManager->addGameObject(newMass);
			tempMass = NULL;
		}
		else {
			delete tempMass;
			tempMass = NULL;
		}
	}
}

void updatePhysics() {
	gameManager->fixedUpdate(FIXED_TIME_STEP);
	if(largeMass && smallMasses.size() > 0) {
		for(size_t i = 0; i < smallMasses.size(); i++) {
			Physics::gravitateTowards(*largeMass, *smallMasses[i]);
			for(size_t j = i + 1; j < smallMasses.size(); j++) {
				Physics::gravitateTowards(*smallMasses[i], *smallMasses[j]);
			}
		}
		// Resolve collisions between masses
		for(size_t i = 0; i < smallMasses.size(); i++) {
			for(size_t j = i + 1; j < smallMasses.size(); j++) {
				CollisionManager::resolveCollisions(*smallMasses[i], *smallMasses[j]);
			}
			CollisionManager::resolveCollisions(*smallMasses[i], *largeMass);
		}
	}
}


void update(int a) {
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (newTime - oldTime) / 1000.0;
	oldTime = newTime;
	lagTime += deltaTime;

	while (lagTime >= FIXED_TIME_STEP) {
		if(!paused) {
			updatePhysics();
		} 
		
		if(getKey(GLUT_KEY_RIGHT)) {
			camera->move(Vector2::Right * WIDTH * FIXED_TIME_STEP);
		}			
		if(getKey(GLUT_KEY_LEFT)) {
			camera->move(Vector2::Left * WIDTH * FIXED_TIME_STEP);
		}
		if(getKey(GLUT_KEY_UP)) {
			camera->move(Vector2::Up * HEIGHT * FIXED_TIME_STEP);
		}	
		if(getKey(GLUT_KEY_DOWN)) {
			camera->move(Vector2::Down * HEIGHT * FIXED_TIME_STEP);
		}	
		if(getKey('n')) {
			// move the camera back to the large mass
			camera->setPosition(largeMass->getTransform()->getPosition());
		}
		if(getKeyUp(' ')) {
			paused = !paused;
		}
		fireNewMass();
		lagTime -= FIXED_TIME_STEP;
		// Reset excessive lag time to prevent jittering when when the PC can't process the logic fast enough 
		if(lagTime > FIXED_TIME_STEP * 2) 
			lagTime = 0;
		updateKeys();
	}
	glutTimerFunc(1, update, a+1);
}

/// <summary>
/// Build Objects Here!!!
/// </summary>
void buildObjects() {
	camera = new Camera(WIDTH, HEIGHT);
	largeMass = new GameObject(Vector2(WIDTH / 2, HEIGHT / 2), 0, "LargeMass");
	largeMass->addComponent(GameObject::createComponent<Renderer>());
	largeMass->addComponent(GameObject::createComponent<Movement>());
	largeMass->getMovement()->setMass(6 * pow(10, 17));
	//largeMass->addComponent(GameObject::createComponent<Tracker>());
	Circle * c1 = new Circle(Vector2(0, 0), 100);
	c1->setColour(1, 1, 1, 1);
	largeMass->getRenderer()->addRenderable(c1);
	largeMass->addComponent(GameObject::createComponent<Collider>()->setShape(new Circle(Vector2(0, 0), 100))->shouldRender(false)->setRestitution(1.0));
	gameManager->addGameObject(largeMass);
}

// Scales the mouse coordinates to account for resizing the window
void setMousePosition(int x, int y) {
	mousePosition.set(((double)x  * coordAspect.x) - camera->getX(), ((double)(newHeight - y) * coordAspect.y) - camera->getY());
}

void motion(int x, int y) {
	setMousePosition(x, y);
}

void mouse(int button, int state, int x, int y) {
	setMousePosition(x, y);
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			mouseDown = true;
			mouseStart = mousePosition;
			break;
		case GLUT_RIGHT_BUTTON:
			camera->setPosition(mousePosition);
			break;
		}
	}
	else if(state == GLUT_UP) {
		switch(button) {
		case GLUT_LEFT_BUTTON:
			mouseDown = false;
			mouseEnd = mousePosition;
			break;
		case GLUT_RIGHT_BUTTON:

			break;
		}
	}
}

void idle(void) {
	glutPostRedisplay();
}


void reshape(int w, int h) { 
	if(h == 0) h = 1;
	if(w == 0) w = 1;
	newWidth = (double)w; newHeight = (double)h;
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
	coordAspect.set(WIDTH / newWidth, HEIGHT / newHeight);
}

void keyup(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void keydown(unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void specialkeyup(int key, int x, int y) {
	keyStates[key] = false;
}

void specialkeydown(int key, int x, int y) {
	keyStates[key] = true;
}


void main(int argA, char** argB) {
	glutInit(&argA, argB);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize((int)WIDTH, (int)HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Interactive Physical Modelling - Team Neilson");
	
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1, update, 0);
	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(specialkeydown);
	glutSpecialUpFunc(specialkeyup);
	glLineWidth(4);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutMotionFunc(motion);
	glutIdleFunc(idle);
	
	buildObjects();
	glutMainLoop();
}