#pragma once
#include <iostream>
#include <sstream>
#include "Vec.hpp"
#include "Material.hpp"
#include "Shape.hpp"

using namespace std;

class Sphere : public Shape {
protected:
	Vector centre;
	double radius;
public:	
	Sphere(const string &s);
	Sphere(Vector centre, double radius, Material material);
	Vector GetNormal(const Vector& P);
	double Intersect(const Vector& O, const Vector& D);
};

Sphere::Sphere(const string &s){
	stringstream ss(s);
	ss >> centre >> radius >> material;
}

Sphere::Sphere(Vector centre, double radius, Material material){
	this->radius = radius;
	this->centre = centre;
	this->material = material;
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