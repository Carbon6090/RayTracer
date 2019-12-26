#pragma once
#include <iostream>

using namespace std;

struct Material { 
	Vector color; // цвет 
	double specular; // блеск 
	vector<double> albedo; // коэффициенты смешивания 
	double refractive; // коэффициент преломления

	friend istream& operator>>(istream& is, Material& material);
};

istream& operator>>(istream& is, Material& m) {
	m.albedo = vector<double>(4);
	return is >> m.color >> m.specular >> m.albedo[0] >> m.albedo[1] >> m.albedo[2] >> m.albedo[3] >> m.refractive;
}