// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include "artisan/raytracer/tracer/tracer.h"
#include "artisan/raytracer/geometry/sphere.h"
#include "artisan/raytracer/material/lambertian.h"
#include "artisan/raytracer/material/metal.h"

using namespace artisan_gfx;

using std::make_shared;

int main()
{
	RayGenerator cam(Point3({-2, 2, 1}), Point3({0, 0, -1}), Vec3({0, 1, 0}), 90, 16.0/9.0);
	MaterialHittableList world;
	int image_height = 225;
	int max_depth = 50;
	int samples_per_pixel = 100;
	int t_max = 1000000;

	

  //ground
	world.Add(
		make_shared<MaterialHittable>(	
			make_shared<Lambertian>(Color({0.5, 0.5, 0.0})),
			make_shared<Sphere>(Point3({0,-100.5,-1}), 100)
		)
	);

  //ball bois

	//center ball
	world.Add(
		make_shared<MaterialHittable>(	
			make_shared<Lambertian>(Color({.7, .3, 0.3})),
			make_shared<Sphere>(Point3({0, 0, -1.5}), 0.5)
		)
	);
	//left ball
	//
	world.Add(
		make_shared<MaterialHittable>(	
			make_shared<Lambertian>(Color({.7, .3, 0.3})),
			make_shared<Sphere>(Point3({-1, 0, -1}), 0.5)
		)
	);


	Tracer ray_tracer(
			cam,
			world,
			image_height,
			max_depth,
			samples_per_pixel,
			t_max);

	PPM rendered_image = ray_tracer.GetRenderedImage();
		
  std::cout << rendered_image.FileContents();
    
}
