#include "Camera.h"
#include "MyMath.h"
#include <gl/glut.h>

Camera::Camera(const double & width, const double & height) {
	position = Vector2(0, 0);
	this->width = width; this->height = height;
	halfWidth = width / 2; halfHeight = height / 2;
	gluOrtho2D(0, width, 0, height);
}

Camera::~Camera() {
}

void Camera::move(const double & x, const double & y) {
	double newX = -x, newY = -y;

	position.add(newX, newY);
	glTranslated(newX, newY, 0);

}

void Camera::move(const Vector2 & amount) {
	move(amount.x, amount.y);
}

Vector2 Camera::getPosition() {
	return position;
}

void Camera::setPosition(const double & x, const double & y) {
	move(x - halfWidth, y - halfHeight);
}

void Camera::setPosition(const Vector2 & newPosition) {
	setPosition(newPosition.x+position.x, newPosition.y+position.y);
}

double Camera::getX() {
	return position.x;
}

double Camera::getY() {
	return position.y;
}