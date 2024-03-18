#include "ray.h"
#include "vec3.h"

namespace artisan_gfx {

Ray::Ray() = default;
Ray::Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

Point3 Ray::origin() const { return orig; }

Vec3 Ray::direction() const { return dir; }

Point3 Ray::at(double t) const {
	return orig + t * dir;
}

bool operator==(const Ray& u, const Ray& v) {
	return u.origin() == v.origin() && 
		u.direction() == v.direction();
}

} // namespace artisan_gfx
