#pragma once
#include "artisan/raytracer/material/material.h"

namespace artisan_gfx {

class Lambertian : public Material {
	public:
		Color albedo;
		Lambertian(const Color &a);
		virtual bool Scatter(const Ray& r, const HitRecord& hr, scatter_record& sr) const override;
};

} // namespace artisan_gfx
