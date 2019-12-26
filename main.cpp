#include <iostream>
#include <ctime>
#include "RayTracer.hpp"

using namespace std;

int main(){
	srand(time(0));
	RayTracer tracer(800, 800);

	Scene scene("scene.txt");
	tracer.Trace(scene);
}