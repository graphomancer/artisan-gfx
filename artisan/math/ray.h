#pragma once
#include "vec3.h"
#include <math.h>

namespace artisan_gfx {

class Ray {
	Point3 orig;
	Vec3 dir;
public:
	Ray();
	Ray(const Point3& origin, const Vec3& direction);
	Point3 origin() const;
	Vec3 direction() const;

	Point3 at(double t) const;
};

bool operator==(const Ray& u, const Ray& v);

} // namespace artisan_gfx
