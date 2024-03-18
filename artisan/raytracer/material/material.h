#pragma once
#include "artisan/raytracer/geometry/hittable.h"
#include "artisan/math/vec3.h"
#include "artisan/math/ray.h"

namespace artisan_gfx {

struct scatter_record {
	Color attenuation;
	Ray direction;
};

class Material {
	public:
		virtual bool Scatter(
			const Ray& direction, const HitRecord& hr, scatter_record& sr
		) const = 0;
};

} // namespace artisan_gfx
