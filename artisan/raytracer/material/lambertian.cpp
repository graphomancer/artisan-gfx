#include "artisan/raytracer/material/lambertian.h"

namespace artisan_gfx {

Lambertian::Lambertian(const Color&a) : albedo(a) {}
bool Lambertian::Scatter(const Ray& r, const HitRecord& hr, scatter_record& sr) const {
	sr.direction = Ray(hr.p, hr.normal + RandomVectorInUnitSphere());
	sr.attenuation = albedo;
	return true;
}

} // namespace artisan_gfx
