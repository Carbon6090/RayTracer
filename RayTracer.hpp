#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "Bitmap.hpp"
#include "Vec.hpp"
#include "Material.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "Scene.hpp"

using namespace std;

const int MAX_DEPTH = 5;

class RayTracer{
	int width;
	int height; 

	bool RefractRay(const Vector &I, const Vector &N, double eta1, double eta2, Vector &D);
	Vector TraceRay(Scene &scene, const Vector& O, const Vector& D, double tmin, double tmax, int depth);
public:
	RayTracer(int width, int height);
	void Trace(Scene &scene);
};

RayTracer::RayTracer(int width, int height){
	this->width = width;
	this->height = height;
}

bool RayTracer::RefractRay(const Vector &I, const Vector &N, double eta1, double eta2, Vector &D){
	double eta;
	int sign;
	double cos = -(I * N);
	if (cos < 0){
		eta = eta1/eta2;
		sign = 1;
	}
	else {
		eta = eta2/eta1;
		sign = -1;
	}

	double k = 1 - eta * eta * (1 - cos * cos);
	if (k < 0)
		return false;
	D = I * eta + N * (eta * cos + sign * sqrt(k));
	return true;
}

Vector RayTracer::TraceRay(Scene &scene, const Vector& O, const Vector& D, double tmin, double tmax, int depth){
	double closest_t;	
	int closest_index = scene.ClosestIntersection(O, D, tmin, tmax, closest_t);
	
	if (closest_index < 0)
		return Vector(0.2, 0.7, 0.8);
	
	Vector P = O + D*closest_t;
	Shape *shape = scene[closest_index]; 
	Vector N = shape->GetNormal(P);
	Material material = shape->GetMaterial();

	Vector diffuse, specular;
	scene.ComputeLightning(P, N, D, material, diffuse, specular);

	Vector color = shape->GetColor(P) ^ (diffuse * material.albedo[0]) + specular * material.albedo[1];

	if (depth <= 0)
		return color;

	if (material.albedo[2] != 0){
		Vector reflect_ray = (-D).ReflectRay(N);
		Vector reflect_color = TraceRay(scene, P, reflect_ray, 0.001, INF, depth - 1);
		color = color + reflect_color * material.albedo[2];
	}

	if (material.albedo[3] != 0) {
		Vector refract_ray;
		if (RefractRay(D, N, material.refractive, 1, refract_ray)){
			Vector refract_color = TraceRay(scene, P + N * 0.001, refract_ray, 0.01, INF, depth - 1);
			color = color + refract_color * material.albedo[3];
		}
	}

	return color;
}

void RayTracer::Trace(Scene &scene){
	Bitmap image(width, height);
	Vector O(0, 0, 0);

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			Vector D((double)j / width - 0.5, 0.5 - (double)i / height, 1);
			D.Normalize();
			Vector color = TraceRay(scene, O, D, 0, INF, MAX_DEPTH);
			int r = min(255.0, color.GetX() * 255);
			int g = min(255.0, color.GetY() * 255);
			int b = min(255.0, color.GetZ() * 255);

			image.set_pixel(j, i, r, g, b);
		}
	}
		
	image.save_image("image.bmp");
}