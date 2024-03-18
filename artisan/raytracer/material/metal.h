#pragma once
#include "artisan/raytracer/material/material.h"

namespace artisan_gfx {

class Metal : public Material {
	public:
		double fuzz;
		Color albedo;
		Metal (const Color &a, const double fuzz);
		virtual bool Scatter(const Ray& r, const HitRecord& hr, scatter_record& sr) const override;
};

} // namespace artisan_gfx
