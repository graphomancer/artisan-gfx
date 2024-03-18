#include <iostream>
#include "tracer.h"
#include "artisan/math/stats.h"

namespace artisan_gfx {

Tracer::Tracer(RayGenerator cam,
		MaterialHittableList world,
		int image_height,
		int max_depth,
		int samples_per_pixel,
		int t_max) {
	this->cam = cam;
	this->world = world;
	this->image_height = image_height;
	this->image_width = image_height * cam.GetAspectRatio();
	this->max_depth = max_depth;
	this->samples_per_pixel = samples_per_pixel;
	this->t_max = t_max;
}

Pixel Tracer::GetPixelColor(int height_coordinate, int width_coordinate) {
	Color c({0,0,0});
	for(int i = 0; i < samples_per_pixel; i++) {
		double sample_jitter = 0;
		if (i > 0) {
			sample_jitter =  RandomDouble(0.0,1.0);
		}
		double width_offset = (width_coordinate + sample_jitter)/image_width;
		double height_offset = (height_coordinate + sample_jitter)/image_height;
		Ray r = cam.GetRay(width_offset, height_offset);
		c = c + GetRayColor(r, max_depth);
	}

	// gamma correction
	double scale = 1.0 / samples_per_pixel;
	c[0] = sqrt(scale * c[0]);
	c[1] = sqrt(scale * c[1]);
	c[2] = sqrt(scale * c[2]);

	return Pixel {
		static_cast<int>(255.0 * c[0]),
		static_cast<int>(255.0 * c[1]),
		static_cast<int>(255.0 * c[2]) 
	};
}
Color Tracer::GetRayColor(Ray& r, int depth) {
	if(depth == 0) {
		return Color({0,0,0});
	}
	HitRecord hr;
	MaybeMaterialHittable mmh = world.Hit(r, 0.001, t_max, hr);
	if( mmh.first ) {
		scatter_record sr;
		mmh.second->Scatter(r, hr, sr);
		return MultiplyVectorElements(sr.attenuation, GetRayColor(sr.direction, depth - 1));
	}
	double grad_coefficient = 0.5 * (Normalize(r.direction())[1] + 1.0);
	return ((1.0 - grad_coefficient) * Color({1.0, 1.0, 1.0}) + grad_coefficient * Color({0.5, 0.7, 1.0}));
}

Color Tracer::RayNormalColorized(Ray& r, HitRecord& hr) {
	return 0.5 * Color({hr.normal[0] + 1., hr.normal[1] + 1., hr.normal[2] + 1.});
}

PPM Tracer::GetRenderedImage() {
	PixelGrid pg;
	for(int i = this->image_height - 1; i >= 0; i--) {
		PixelRow pr;
		for(int j = 0; j < this->image_width; j++) {
			pr.push_back(GetPixelColor(i, j));
		}
		pg.push_back(pr);
	}
	return PPM(pg, 255);
}

} // namespace artisan_gfx
