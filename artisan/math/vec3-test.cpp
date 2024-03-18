#include "gtest/gtest.h"
#include "vec3.h"

namespace artisan_gfx {

const Vec3 A = Vec3({2, 3, 6}); // pythagorean quad, magnitude 7 
const Vec3 B = Vec3({1, 4, 8}); // pythagorean quad, magnitude 9
const Vec3 C = Vec3({-1, 1, 2}); // C = B - A

TEST(Vec3Test, TestUnaryVecOps) {
	EXPECT_EQ(A.MagnitudeSquared(), 49);
	EXPECT_EQ(Magnitude(A), 7);
	EXPECT_EQ(Normalize(A), Vec3({2. / 7, 3. / 7, 6. / 7}));
}

TEST(Vec3Test, TestBinaryVecOps) {
	EXPECT_EQ(A + B, Vec3({3, 7, 14}));
	EXPECT_EQ(A - B, Vec3({1, -1, -2}));
	EXPECT_EQ(A * B, 1 * 2 + 3 * 4 + 6 * 8);
	EXPECT_EQ(2. * A, Vec3({4, 6, 12}));
	EXPECT_EQ(A == Vec3({2, 3, 6}), true);
	EXPECT_EQ(A / 2., Vec3({1, 1.5, 3}));
	EXPECT_EQ(Cross(A, B), Vec3({0, -10, 5}));
	EXPECT_EQ(Cross(B, A), Vec3({0, 10, -5}));
}

TEST(Vec3Test, TestDistance) {
	EXPECT_EQ(DistanceBetween(C,B), 7);
}

} // namespace artisan_gfx
