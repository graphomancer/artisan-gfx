#include "gtest/gtest.h"
#include <memory>
#include <vector>
#include "artisan/raytracer/geometry/sphere.h"
#include "artisan/raytracer/material/lambertian.h"
#include "material-hittable-list.h"

namespace artisan_gfx {


double sphere_radius = 3;
Point3 origin = Point3({0, 0, 0});
Point3 distant_point = Point3({50, 0, 0});
Vec3 x_hat = Vec3({1, 0, 0});


shared_ptr<Material> mtrl = make_shared<Lambertian>(Color({.5,.5,.5}));
shared_ptr<Sphere> sphere_centered_at_origin = make_shared<Sphere>(origin, sphere_radius);
shared_ptr<Sphere> sphere_centered_at_distant_point = make_shared<Sphere>(distant_point, sphere_radius);

MaterialHittableList world(vector<shared_ptr<MaterialHittable>> {
		make_shared<MaterialHittable>(mtrl, sphere_centered_at_origin),
		make_shared<MaterialHittable>(mtrl, sphere_centered_at_distant_point)
});

TEST(HittableListTest, RayHits) {
	Ray ray_at_origin = Ray(origin, x_hat);
	Ray ray_between_spheres = Ray(Point3({25, 0, 0}), x_hat);
	HitRecord rec;

	MaybeMaterialHittable hit = world.Hit(ray_at_origin, -100, 100, rec);
	EXPECT_EQ(hit.first, true);
	EXPECT_EQ(rec.p[0], 3.0);
	EXPECT_EQ(rec.p[1], 0);
	EXPECT_EQ(rec.p[2], 0);
	EXPECT_EQ(rec.normal, -1. * x_hat);

	hit = world.Hit(ray_between_spheres, -100, 100, rec);
	EXPECT_EQ(hit.first, true);
	EXPECT_EQ(rec.p[0], 47.0);
	EXPECT_EQ(rec.p[1], 0);
	EXPECT_EQ(rec.p[2], 0);
	EXPECT_EQ(rec.normal, -1. * x_hat);
}

TEST(HittableListTest, RayDoesNotHit) {
	Ray ray_on_y_axis = Ray(Point3({0, 25, 0}), x_hat);
	HitRecord rec;

	MaybeMaterialHittable hit = world.Hit(ray_on_y_axis, -100, 100, rec);
	EXPECT_EQ(hit.first, false);
}

} // namespace artisan_gfx
