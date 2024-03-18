#include "gtest/gtest.h"
#include "vec4.h"

namespace artisan_gfx {

TEST(Vec4Test, HomogeneousPointTest) {
	Vec3 A = Vec3({2,4,6});
	Vec4 H = ToHomogeneousPoint(A);
	for(int i = 0; i < 3; i++) {
		EXPECT_EQ(A[i], H[i]);
	}
	EXPECT_EQ(H[3], 1);

	H[3] = 2;

	Vec3 B = FromHomogeneousPoint(H);

	for(int i = 0; i < 2; i++) {
		EXPECT_EQ(B[i], A[i]/2);
	}
}

} // namespace artisan_gfx
