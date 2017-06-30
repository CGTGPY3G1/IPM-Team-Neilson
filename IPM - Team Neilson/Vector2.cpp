#include "Vector2.h"
#include "MyMath.h"
#include <cmath>


const Vector2 Vector2::Up = Vector2(0.0, 1.0), Vector2::Down = Vector2(0.0, -1.0), Vector2::Left = Vector2(-1.0, 0.0), Vector2::Right = Vector2(1.0, 0.0), Vector2::Zero = Vector2(0.0, 0.0), Vector2::One = Vector2(1.0, 1.0);

Vector2::Vector2() {
	x = 0.0; this->y = 0.0;
}

Vector2::Vector2(const double & x, const double & y) {
	this->x = x; this->y = y;
}

Vector2::~Vector2() {
}

Vector2 Vector2::set(const double & x, const double & y) {
	this->x = x; this->y = y;
	return *this;
}

Vector2 Vector2::set(const Vector2 & toSet) {
	x = toSet.x; y = toSet.y;
	return *this;
}

Vector2 Vector2::operator = (const Vector2 & toSet) {
	x = toSet.x; y = toSet.y;
	return *this;
}

Vector2 Vector2::add(const double & x, const double & y) {
	this->x += x; this->y += y;
	return *this;
}

Vector2 Vector2::operator + (const Vector2 & toAdd) {
	return Vector2(x + toAdd.x, y + toAdd.y);
}

const Vector2 Vector2::operator+(const Vector2 & toAdd) const {
	return Vector2(x + toAdd.x, y + toAdd.y);
}

Vector2 Vector2::operator += (const Vector2 & toAdd) {
	x += toAdd.x; y += toAdd.y;
	return *this;
}

Vector2 Vector2::subtract(const double & x, const double & y) {
	this->x -= x; this->y -= y;
	return *this;
}

Vector2 Vector2::operator - (const Vector2 & toSubtract) {
	return Vector2(x - toSubtract.x, y - toSubtract.y);
}

Vector2 Vector2::operator - () {
	return Vector2(-x, -y);
}

const Vector2 Vector2::operator - (const Vector2 & toSubtract) const {
	return Vector2(x - toSubtract.x, y - toSubtract.y);
}

Vector2 Vector2::operator -= (const Vector2 & toSubtract) {
	x -= toSubtract.x; y -= toSubtract.y;
	return *this;
}

Vector2 Vector2::scale(const double & scalar) {
	this->x *= x; this->y *= y;
	return *this;
}

Vector2 Vector2::operator * (const double & scalar) {
	return Vector2(x * scalar, y * scalar);
}

const Vector2 Vector2::operator*(const double & scalar) const {
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator *= (const double & scalar) {
	x *= scalar; y *= scalar;
	return *this;
}

Vector2 Vector2::operator / (const double & scalar) {
	return Vector2(x / scalar, y / scalar);
}

const Vector2 Vector2::operator/(const double & scalar) const {
	return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator /= (const double & scalar) {
	x /= scalar; y /= scalar;
	return *this;
}

double Vector2::dot(const Vector2 & other) {
	return dot(other.x, other.y);
}

double Vector2::dot(const double & x, const double & y) {
	return (this->x * x) + (this->y * y);
}

double Vector2::squareMagnitude() {
	return x * x + y * y;
}

double Vector2::magnitude() {
	double sqr = squareMagnitude();
	return (sqr == 0.0 || sqr == 1.0) ? sqr : sqrt(sqr);
}

Vector2 Vector2::normalize() {
	double mag = magnitude();
	if(mag != 0.0 && mag != 1.0) {
		x /= mag;
		y /= mag;
	}
	return *this;
}

Vector2 Vector2::normalized() {
	double x = this->x, y = this->y;
	double length = magnitude();
	if(length != 0.0 && length != 1.0) {
		x /= length;
		y /= length;
	}
	return Vector2(x, y);
}

double Vector2::angleInRadians() {
	return atan2(y, x);
}

Vector2 Vector2::rotateInRadians(const double & angle) {
	double cosine = cos(angle), sine = sin(angle);
	double rotatedX = (x * cosine) - (y * sine), rotatedY = (x * sine) + (y * cosine);
	x = rotatedX; y = rotatedY;
	return *this;
}

Vector2 Vector2::rotatedInRadians(const double & angle) {
	return Vector2(x, y).rotateInRadians(angle);
}

Vector2 Vector2::flip90(const bool & clockwise) {
	double oldX = x;
	if(clockwise) {
		x = y; y = -oldX;
	}
	else {
		x = -y; y = oldX;
	}
	return *this;
}

Vector2 Vector2::copy() {
	return Vector2(x, y);
}