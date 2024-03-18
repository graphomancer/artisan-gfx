#include "artisan/raytracer/material/metal.h"

namespace artisan_gfx {

Metal::Metal(const Color&a, const double fuzz) : albedo(a),
	fuzz(fuzz * fuzz > 1 ? 1 : fuzz) {}
bool Metal::Scatter(const Ray& r, const HitRecord& hr, scatter_record& sr) const {
	sr.direction = Ray(hr.p,
		r.direction() - 2 *( r.direction() * hr.normal) * hr.normal
				+ fuzz * RandomVectorInUnitSphere()
	);
	sr.attenuation = albedo;
	return true;
}

} // namespace artisan_gfx
