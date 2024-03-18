#pragma once
#include "hittable.h"
#include "artisan/math/vec3.h"
#include "artisan/math/ray.h"

namespace artisan_gfx {


class Sphere : public Hittable 
{
	Point3 center;
	double radius;
public:
	Sphere();
	Sphere(const Point3& center, const double radius);
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace artisan_gfx
