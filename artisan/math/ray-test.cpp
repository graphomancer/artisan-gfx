#include "gtest/gtest.h"
#include "ray.h"

namespace artisan_gfx {

const Ray r(Point3({1, 1, 1}), Vec3({0, 1, 1}));

TEST(RayTest, TestGetters) {
	EXPECT_EQ(r.origin(), Point3({1, 1, 1}));
	EXPECT_EQ(r.direction(), Vec3({0, 1, 1}));
}

TEST(RayTest, TestAt) {
	EXPECT_EQ(r.at(2), Point3({1, 3, 3}));
	EXPECT_EQ(r.at(0), Point3({1, 1, 1}));
	EXPECT_EQ(r.at(-1), Point3({1, 0, 0}));
}

TEST(RayTest, RayEq) {
	EXPECT_EQ(r, Ray(r.origin(), r.direction()));
}

} // namespace artisan_gfx
