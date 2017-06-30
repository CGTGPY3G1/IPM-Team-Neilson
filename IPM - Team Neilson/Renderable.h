#pragma once
#include "Vector2.h"
typedef enum {
	DO_NOT_RENDER = -1,
	RENDER_SHAPE = 0,
	RENDER_IMAGE = 1
} RenderType;

class Renderable {
public:
	Renderable();
	~Renderable();
	Vector2 getPosition();
	void setPosition(const Vector2 & newCenter);
	/*virtual void setRotation(Vector2 & newRotation) = 0;
	virtual void setRotation(const double & newRotation) = 0;*/
	virtual void draw(Vector2 & origin, const double & rotation) = 0;
	virtual RenderType getRenderType() = 0;
	int getRenderableID();
	void setEnabled(bool & enabled);
	void setSortOrder(int & sortOrder);
	int getSortOrder();
	friend bool operator<(const Renderable & a, const Renderable & b);
	friend bool operator==(const Renderable & a, const Renderable & b);
	friend bool operator!=(const Renderable & a, const Renderable & b);
protected:
	static int rIdCounter;
	static int getNewID();
	bool enabled = false, initialized = false;
	int sortOrder = 0, renderableID = -1;
	double rotation = 0;
	Vector2 center;
};