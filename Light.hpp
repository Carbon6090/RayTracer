#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "Bitmap.hpp"
#include "Vec.hpp"
#include "Sphere.hpp"

using namespace std;

const int AMBIENT = 0; 
const int POINT = 1; 
const int DIRECTIONAL = 2; 	

class Light {
public:
	int type;
	Vector vector;
	Vector intensity;
	Light(const string& path);
	Light(Vector intensity);
	Light(int type, Vector intensity, Vector vec);
};

Light::Light(const string& path){
	stringstream ss(path);
	ss >> type >> intensity;

	if (type != AMBIENT)
		ss >> vector;
}

Light::Light(Vector intensity){
	type = 0;
	this->intensity = intensity;
}

Light::Light(int type, Vector intensity, Vector vector){
	this->type = type;
	this->intensity = intensity;
	this->vector = vector;
}