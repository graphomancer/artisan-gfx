#include "ray-generator.h"
#include <cmath>

namespace artisan_gfx {
using namespace std;

RayGenerator::RayGenerator(Point3 lookfrom, Point3 lookat, Vec3 vup, double field_of_view_degrees, double aspect_ratio) : origin(Vec3({0,0,0})), focal_length(Vec3({0,0,0})), viewport_width(Vec3({0,0,0})), viewport_height(Vec3({0,0,0})), lower_left_corner(Vec3({0,0,0}))   {
	double field_of_view_radians = DegreesToRadians(field_of_view_degrees);
	this->aspect_ratio = aspect_ratio;
	double height_length = 2 * tan(field_of_view_radians/2.);

	Vec3 depth_hat = Normalize((lookfrom - lookat));
	Vec3 width_hat = Normalize((Cross(vup, depth_hat)));
	Vec3 height_hat = Cross(depth_hat, width_hat);

	this->origin = lookfrom;
	this->focal_length = depth_hat;

	this->viewport_height = height_length * height_hat; // Vec3(0.0, height_length, 0.0);
	this->viewport_width = aspect_ratio * height_length * width_hat;
	lower_left_corner = this->origin
		- this->viewport_width / 2.
		- this->viewport_height / 2.
		- this->focal_length;
}

RayGenerator::RayGenerator() : RayGenerator(Point3({0,0,0}), Point3({0,0, -1}), Vec3({0,1,0}), 90.0, 16.0/9.0) {}

Ray RayGenerator::GetRay(double width_percentage, double height_percentage) const {
	return Ray(origin, lower_left_corner 
			+ width_percentage * viewport_width
			+ height_percentage * viewport_height
			- origin);
}

} // namespace artisan_gfx
