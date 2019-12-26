#pragma once
#include <iostream>
#include <cmath>

#include "Vec.hpp"
#include "Material.hpp"

using namespace std;

const double INF = 1e300;

class Shape {
protected:
	Material material;
public:	
	virtual Vector GetNormal(const Vector& P) = 0;
	virtual double Intersect(const Vector& O, const Vector& D) = 0;
	virtual Vector GetColor(const Vector& P);
	Material GetMaterial() const;
};

Vector Shape::GetColor(const Vector& P) {
	return material.color;
}

Material Shape::GetMaterial() const{
	return material;
}