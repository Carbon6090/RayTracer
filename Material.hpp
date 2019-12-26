#pragma once
#include <iostream>

using namespace std;

struct Material { 
	Vector color; // цвет 
	double specular; // блеск 
	vector<double> albedo; // коэффициенты смешивания 
	double refractive; // коэффициент преломления

	string ToString();
	void Random();
	friend istream& operator>>(istream& is, Material& material);
};

string Material::ToString(){
	string c = to_string(color.GetX()) + " " + to_string(color.GetY()) + " " + to_string(color.GetZ());
	string alb = to_string(albedo[0]) + " " + to_string(albedo[1]) + " " + to_string(albedo[2]) + " " + to_string(albedo[3]);
	return c + " " + to_string(specular) + " " + alb + " " + to_string(refractive);
}

void Material::Random(){
	color = Vector(rand() * 1.0 / RAND_MAX, rand() * 1.0 / RAND_MAX, rand() * 1.0 / RAND_MAX);
	specular = rand() % 2000;
	albedo = vector<double>(4);
	albedo[0] = rand() * 1.0 / RAND_MAX;
	albedo[1] = rand() * 10.0 / RAND_MAX;
	albedo[2] = rand() * 1.0 / RAND_MAX;
	albedo[3] = rand() * 1.0 / RAND_MAX;
	refractive = 0.75 + (rand() * 0.5) / RAND_MAX;
}

istream& operator>>(istream& is, Material& m) {
	m.albedo = vector<double>(4);
	return is >> m.color >> m.specular >> m.albedo[0] >> m.albedo[1] >> m.albedo[2] >> m.albedo[3] >> m.refractive;
}