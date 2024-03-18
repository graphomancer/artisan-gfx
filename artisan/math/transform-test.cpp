#include "gtest/gtest.h"
#include "transform.h"

namespace artisan_gfx {

TEST(TransformTest, viewportTest) {
	Mat4 viewport = ViewportTransform(0,0,800,800);
	Vec4 t = Vec4({1,1,.5,1});
	Vec4 tprime = viewport * t;
	EXPECT_DOUBLE_EQ(tprime[0], 800);
	EXPECT_DOUBLE_EQ(tprime[1], 800);
	EXPECT_DOUBLE_EQ(tprime[2], .5);
}

} // namespace artisan_gfx
