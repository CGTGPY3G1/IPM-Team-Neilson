#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderable.h"
#include <algorithm>

Renderer::Renderer() : Component(true, "Renderer") {
}

Renderer::~Renderer() {
}

void Renderer::setSortOrder(const int & sortOrder) {
	this->sortOrder = sortOrder;
}

int Renderer::getSortOrder() {
	return sortOrder;
}

void Renderer::draw() {
	if (toRender.size() > 0) {
		Transform * t = gameObject->getTransform();
		Vector2 position = t->getPosition(); double rotation = t->getRotation().angleInRadians();
		for (std::vector<Renderable*>::iterator i = toRender.begin(); i != toRender.end(); ++i) {
			(*i)->draw(position, rotation);
		}
	}
}

bool sortRenderables(Renderable * a, Renderable * b) {
	return (a->getSortOrder() < b->getSortOrder());
}

void Renderer::addRenderable(Renderable * toAdd) {
	toRender.push_back(toAdd);
	std::sort(toRender.begin(), toRender.end(), sortRenderables);
}

void Renderer::removeRenderable(Renderable * toRemove) {
	if (toRender.size() != 0) {
		if (std::find(toRender.begin(), toRender.end(), toRemove) != toRender.end()) 
			toRender.erase(std::remove(toRender.begin(), toRender.end(), toRemove), toRender.end());
	}
}

ComponentID Renderer::getComponentID() {
	return RENDERER_COMPONENT;
}

void Renderer::initialize() {

}

void Renderer::setSortLayer(const int & sortLayer) {
	this->sortLayer = sortLayer;
}

int Renderer::getSortLayer() {
	return sortLayer;
}

void Renderer::update() {
	draw();
}

bool operator < (const Renderer & a, const Renderer & b) {
	return a.sortLayer < b.sortLayer ? true : a.sortOrder < b.sortOrder ? true : false;
}

bool operator == (const Renderer & a, const Renderer & b) {
	return (a.compID == a.compID);
}

bool operator != (const Renderer & a, const Renderer & b) {
	return !(a == b);
}

