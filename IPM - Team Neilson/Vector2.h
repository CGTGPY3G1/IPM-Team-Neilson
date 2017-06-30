#pragma once
#include<iostream>
class Vector2 {
public:
	const static Vector2 Up, Down, Left, Right, Zero, One;
	double x, y;
	Vector2();
	Vector2(const double & x, const double & y);
	~Vector2();
	Vector2 set(const double & x, const double & y);
	Vector2 set(const Vector2 & toSet);
	Vector2 operator = (const Vector2 & toSet);
	Vector2 add(const double & x, const double & y);
	Vector2 operator + (const Vector2 & toAdd);
	const Vector2 operator + (const Vector2 & toAdd) const;
	Vector2 operator += (const Vector2 & toAdd);
	Vector2 subtract(const double & x, const double & y);
	Vector2 operator - (const Vector2 & toSubtract);
	Vector2 operator - ();
	const Vector2 operator - (const Vector2 & toSubtract) const;
	Vector2 operator -= (const Vector2 & toSubtract);
	Vector2 scale(const double & scalar);
	Vector2 operator * (const double & scalar);
	const Vector2 operator * (const double & scalar) const;
	Vector2 operator *= (const double & scalar);
	Vector2 operator / (const double & scalar);
	const Vector2 operator / (const double & scalar) const;
	Vector2 operator /= (const double & scalar);
	double dot(const Vector2 & other);
	double dot(const double & x, const double & y);

	Vector2 normalize();
	Vector2 normalized();
	double squareMagnitude();
	double magnitude();
	double angleInRadians();
	Vector2 rotateInRadians(const double & angle);
	Vector2 rotatedInRadians(const double & angle);
	Vector2 flip90(const bool & clockwise);
	Vector2 copy();
	friend std::ostream & operator << (std::ostream & out, const Vector2 toPrint) {
		return out << "X = " << toPrint.x << " Y = " << toPrint.y;
	}
	
};