#pragma once
#include "artisan/math/vec3.h"
#include "artisan/math/ray.h"

namespace artisan_gfx {

struct HitRecord {
	Point3 p;
	Vec3 normal;
};

class Hittable {
	public:
		virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0; 
};

} // namespace artisan_gfx
