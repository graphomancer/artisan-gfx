#include "gtest/gtest.h"
#include <vector>
#include "sphere.h"

namespace artisan_gfx {


double sphere_radius = 3;
Point3 origin = Point3({0, 0, 0});
Point3 distant_point = Point3({100, 0, 0});

Sphere sphere_centered_at_origin = Sphere(origin, sphere_radius) ;
Sphere sphere_centered_at_distant_point = Sphere(distant_point, sphere_radius);

Vec3 x_hat = Vec3({1,0,0});
Vec3 y_hat = Vec3({0,1,0});

TEST(SphereTest, RayAtOriginIntersectsSphereAtOrigin) {
	Ray ray_at_origin = Ray(origin, x_hat);
	HitRecord rec;
	bool hit = sphere_centered_at_origin.Hit(ray_at_origin, -100, 100, rec);
	EXPECT_EQ(hit, true);
	EXPECT_EQ(rec.p[0], 3.0);
	EXPECT_EQ(rec.p[1], 0);
	EXPECT_EQ(rec.p[2], 0);
	EXPECT_EQ(rec.normal, -1. * x_hat);
}

TEST(SphereTest, RayAtOriginIntersectsDistantSphere) {
	Ray ray_at_origin = Ray(origin, x_hat);
	HitRecord rec;
	bool hit = sphere_centered_at_distant_point.Hit(ray_at_origin, -100, 100, rec);
	EXPECT_EQ(hit, true);
	EXPECT_EQ(rec.p[0], 97.0);
	EXPECT_EQ(rec.p[1], 0);
	EXPECT_EQ(rec.p[2], 0);

	EXPECT_EQ(rec.normal, -1. * x_hat);
}

TEST(SphereTest, OffsetRayNotIntersectSphereAtOrigin) {
	HitRecord rec;
	bool hit = true;

	Ray offset_ray_x_dir = Ray(origin + Point3({12,0,0}), x_hat);
	hit = sphere_centered_at_origin.Hit(offset_ray_x_dir, -1000, 1000, rec);
	EXPECT_EQ(hit, false);

	Ray offset_ray_y_dir = Ray(origin + Point3({12,0,0}), y_hat);
	hit = sphere_centered_at_origin.Hit(offset_ray_y_dir, -1000, 1000, rec);
	EXPECT_EQ(hit, false);
}

TEST(SphereTest, OffsetRayNotIntersectDistantSphere) {
	HitRecord rec;
	bool hit = true;

	Ray offset_ray_x_dir = Ray(origin + Point3({112,0,0}), x_hat);
	hit = sphere_centered_at_distant_point.Hit(offset_ray_x_dir, -1000, 1000, rec);
	EXPECT_EQ(hit, false);

	Ray offset_ray_y_dir = Ray(origin + Point3({12,0,0}), y_hat);
	hit = sphere_centered_at_distant_point.Hit(offset_ray_y_dir, -1000, 1000, rec);
  	EXPECT_EQ(hit, false);
}

} // namespace artisan_gfx
