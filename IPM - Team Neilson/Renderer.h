#pragma once
#include "Component.h"
#include "Renderable.h"
#include <vector>
using namespace std;

enum RenderLayers {
	LAYER_B = 5,
	LAYER_M = 6,
	LAYER_F = 7
};

class Renderer : public Component
{
public:
	Renderer();
	~Renderer();
	void setSortOrder(const int & sortOrder);
	int getSortOrder();
	void setSortLayer(const int & sortLayer);
	int getSortLayer();
	friend bool operator < (const Renderer & a, const Renderer & b);
	friend bool operator == (const Renderer & a, const Renderer & b);
	friend bool operator != (const Renderer & a, const Renderer & b);
	void update() override;
	void draw();
	void addRenderable(Renderable * toAdd);
	void removeRenderable(Renderable * toRemove);
	ComponentID getComponentID() override;
	void initialize() override;
protected:
	int sortOrder = 0, sortLayer = 0;
	std::vector<Renderable *> toRender;
};

