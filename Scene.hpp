#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include "Shape.hpp"
#include "Light.hpp"

class Scene{
	struct NamedMaterial{
		string name;
		string material;
	};
	vector<Shape*> shapes;
	vector<Light> lights;
	vector<NamedMaterial> materials;

	string GetMaterialByName(string name);

public:	
	Scene();
	Scene(const string& path);
	int ClosestIntersection(const Vector& O, const Vector& D, double tmin, double tmax, double& t);
	bool HaveIntersection(const Vector& O, const Vector& D, double tmin, double tmax);
	void ComputeLightning(const Vector& P, const Vector& N, const Vector& D, Material material, Vector& diffuse, Vector& specular);

	Shape* operator[](int index);
};

string Scene::GetMaterialByName(string name){
	for (int i = 0; i < materials.size(); i++)
		if (name == materials[i].name)
			return materials[i].material;

	return "";
}

Scene::Scene(){
	Material ivory = { Vector(0.4, 0.4, 0.3), 50, { 0.6, 0.3, 0.1, 0.0 }, 1.0}; 
	Material glass = {Vector(0.6, 0.7, 0.8), 125, { 0.0, 0.5, 0.1, 0.8 }, 1.5};
	Material red_rubber = {Vector(0.3, 0.1, 0.1), 10, { 0.9, 0.1, 0.0, 0.0 }, 1.0}; 
	Material mirror = {Vector(1.0, 1.0, 1.0), 1425, { 0.0, 10.0, 0.8, 0.0 }, 1.0};

	// shapes.push_back(new Sphere("2 0 4 1 1 1 1 1425 0 10 0.8 0 1 mirror"));
	shapes.push_back(new Sphere(Vector(2, 0, 4), 1, mirror));
	shapes.push_back(new Sphere(Vector(-2, 0, 4), 1, red_rubber));
	shapes.push_back(new Sphere(Vector(0, -1, 3), 1, glass));
	shapes.push_back(new Sphere(Vector(0, -5001, 0), 5000, ivory));

	lights.push_back(Light(Vector(0.2, 0.2, 0.2)));
	lights.push_back(Light(POINT, Vector(2.4, 2.4, 2.4), Vector(2, 1, 0)));
	lights.push_back(Light(DIRECTIONAL, Vector(0.8, 0.8, 0.8), Vector(1, 4, 4)));
}

Scene::Scene(const string& path) {
	ifstream f(path);

	if (!f)
		throw string("Unable to open file '") + path + "'";

	string line;

	while (getline(f, line)) {
		if (line == "" || line[0] == '#')
			continue;

		stringstream ss(line);
		string name;
		ss >> name;

		if (name == "sphere") {
			string materialName;
			ss >> materialName;
			string description;
			getline(ss, description);

			string material = GetMaterialByName(materialName);

			if (material == "")
				cout << "Unknown material '" << materialName << "'" << endl;

			shapes.push_back(new Sphere(description + " " + material));
		}
		else if (name == "light") {
			string description;
			getline(ss, description);			
			lights.push_back(Light(description));
		}
		else if (name == "material"){
			string materialName, material;
			ss >> materialName;
			getline(ss, material);
			materials.push_back({ materialName, material });
		}
		else {
			cout << "Error: '" << line << "'" << endl;
		}
	}

	f.close();

	lights.push_back(Light(Vector(0.2, 0.2, 0.2)));
	lights.push_back(Light(POINT, Vector(2.4, 2.4, 2.4), Vector(2, 1, 0)));
	lights.push_back(Light(DIRECTIONAL, Vector(0.8, 0.8, 0.8), Vector(1, 4, 4)));
}


int Scene::ClosestIntersection(const Vector& O, const Vector& D, double tmin, double tmax, double& t){
	int index = -1;
	for (int i = 0; i < shapes.size(); i++){
		double t0 = shapes[i]->Intersect(O, D);
		if (t0 >= tmin && t0 < tmax && (t0 < t || index == -1)){
			t = t0;
			index = i;
		}
	}
	return index;
}

bool Scene::HaveIntersection(const Vector& O, const Vector& D, double tmin, double tmax){
	for (int i = 0; i < shapes.size(); i++){
		double t0 = shapes[i]->Intersect(O, D);
		if (t0 >= tmin && t0 < tmax)
			return true;
	}
	return false;
}

void Scene::ComputeLightning(const Vector& P, const Vector& N, const Vector& D, Material material, Vector& diffuse, Vector& specular){
	for (int i = 0; i < lights.size(); i++){
		if (lights[i].type == AMBIENT)
			diffuse = diffuse + lights[i].intensity;
		else{
			Vector L;
			double tmax;

			if (lights[i].type == POINT){
				L = lights[i].vector - P;
				tmax = L.length();
			}
			else {
				L = lights[i].vector;
				tmax = INF;
			}

			L.Normalize();

			if (HaveIntersection(P, L, 0.001, tmax))
				continue;

			// расчёт диффузного освещения
			double LN = L * N;

			if (LN > 0)
				diffuse = diffuse + lights[i].intensity * LN; 

			// расчёт отражающего света
			Vector R = L.ReflectRay(N);
			double specularBr = -(R * D);
			if (specularBr > 0)
				specular = specular + lights[i].intensity * pow(specularBr, material.specular);
		}
	}
}

Shape* Scene::operator[](int index) {
	return shapes[index];
}