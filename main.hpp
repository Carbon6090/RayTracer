#pragma once
#include <iostream>
#include "Vec.hpp"
#include <cmath>

using namespace std;

const double INF = 1e300;

class Sphere{
	Vector centre;
	double radius;
	Vector color;
public:	
	Vector GetNormal(const Vector& P);
	Sphere(Vector centre, double radius, Vector color);
	Vector GetColor();
	double Intersect(const Vector& O, const Vector& D);
};

Sphere::Sphere(Vector centre, double radius, Vector color){
	this->radius = radius;
	this->centre = centre;
	this->color = color;
}

Vector Sphere::GetColor(){
	return color;
}

Vector Sphere::GetNormal(const Vector& P){
	return Vector((P.GetX() - centre.GetX()) / radius, (P.GetY()- centre.GetY()) / radius, (P.GetZ() - centre.GetZ()) / radius);
}

double Sphere::Intersect(const Vector& O, const Vector& D){
	Vector OC = O - centre;
	double val = OC * D;
	double value = val * val - OC * OC + radius*radius;
	
	if (value < 0)
		return INF;

	double disc = sqrt(value);
	double t1 = -(val + disc);

	if (t1 > 0)
		return t1;

	double t2 = disc - val;
	
	if (t1 < 0 && t2 < 0)
		return INF;
	return t2;
}