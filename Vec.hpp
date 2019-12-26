//t = -(OCxD) +- sqrt((OCxD)^2 - (OCxOC) + R^2)) 
#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector{
	double x;
	double y;
	double z;
public:
	Vector();
	Vector(double x, double y, double z);
	double GetX() const;
	double GetY() const;
	double GetZ() const;
	double length();
	Vector operator^(const Vector& v) const;
	Vector operator*(double scalar) const; // умножение вектора на число
	double operator*(const Vector& v) const; // скалярное умножение
	Vector operator-(const Vector& v) const; 
	Vector operator+(const Vector& v) const;
	Vector operator^(double scalar) const;
	Vector operator-() const; 
	Vector ReflectRay(const Vector& N);
	void Normalize();

	friend istream& operator>>(istream& is, Vector& v);
};

Vector::Vector(){
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vector::GetX() const{
	return x;
}

double Vector::GetY() const{
	return y;
}

double Vector::GetZ() const{
	return z;
}

double Vector::length(){
	return x*x + y*y + z*z;
}

Vector Vector::operator^(const Vector& v) const{
	return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vector::operator*(double scalar) const{
	return Vector(x * scalar, y * scalar, z * scalar);
}

double Vector::operator*(const Vector& v) const{
	return (x * v.x + y * v.y + z * v.z);
}

Vector Vector::operator-(const Vector& v) const{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator+(const Vector& v) const{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}

void Vector::Normalize(){
	double length = sqrt(x*x + y*y + z*z);
	if (length == 0)
		return;
	x /= length;
	y /= length;
	z /= length;
}

Vector Vector::ReflectRay(const Vector& N) {
	return N * (2 * (*this * N)) - *this;
}

istream& operator>>(istream& is, Vector& v) {
	return is >> v.x >> v.y >> v.z;
}