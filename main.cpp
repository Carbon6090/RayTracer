#include <iostream>
#include "RayTracer.hpp"

using namespace std;

int main(){
	RayTracer tracer(800, 800);

	Scene scene("scene.txt");
	tracer.Trace(scene);
}