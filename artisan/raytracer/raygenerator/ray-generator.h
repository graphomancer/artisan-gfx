#pragma once
#include "artisan/math/vec3.h"
#include "artisan/math/ray.h"
#include "artisan/math/trig.h"

namespace artisan_gfx {
class RayGenerator {
	public:
		RayGenerator();
		RayGenerator(Point3 lookfrom, Point3 lookat, Vec3 vup, double field_of_view_degrees, double aspect_ratio);
		Ray GetRay(double width_percentage, double height_percentage) const;
		double GetAspectRatio() { return this->aspect_ratio; }
		Vec3 GetViewportWidth() { return this->viewport_width; }
		Vec3 GetViewportHeight() { return this->viewport_height; }
		Point3 GetLowerLeftCorner() { return this->lower_left_corner; }
		Point3 GetOrigin() { return this->origin; }

	private:
		double aspect_ratio;
		Point3 origin;
		Vec3 focal_length;
		Vec3 viewport_width;
		Vec3 viewport_height;
		Point3 lower_left_corner;
};

} // namespace artisan_gfx
