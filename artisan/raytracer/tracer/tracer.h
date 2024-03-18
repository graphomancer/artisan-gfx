#pragma once
#include "artisan/raytracer/raygenerator/ray-generator.h"
#include "artisan/file/ppm.h"
#include "artisan/raytracer/materialhittable/material-hittable-list.h"

namespace artisan_gfx {
class Tracer {
	int image_width;	
	int image_height;
	int max_depth;
	int samples_per_pixel;
	double t_max;
	RayGenerator cam;
	MaterialHittableList world;
  Color ReflectedRayColor(Ray& r, HitRecord& hr, int depth);
  Color RayNormalColorized(Ray& r, HitRecord& hr);
public:
	Tracer(RayGenerator cam,
			MaterialHittableList world,
			int image_height,
			int max_depth,
			int samples_per_pixel,
			int t_max);
	Pixel GetPixelColor(int width_coordinate, int height_coordinate);
	Color GetRayColor(Ray & r, int depth);
	PPM GetRenderedImage();
};

} // namespace artisan_gfx
