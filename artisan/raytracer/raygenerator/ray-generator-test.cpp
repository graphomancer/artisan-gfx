#include "gtest/gtest.h"
#include "ray-generator.h"

namespace artisan_gfx {

Vec3 origin({0,0,0});
RayGenerator cam(Point3({0,0,0}), Point3({0, 0, -1}), Vec3({0, 1,0}), 90, 1);

TEST(CameraTest, TestGetRay) {
	cam.GetViewportHeight();

	EXPECT_FLOAT_EQ(cam.GetViewportHeight()[1], 2);
	EXPECT_FLOAT_EQ(cam.GetViewportHeight()[0], 0);
	EXPECT_FLOAT_EQ(cam.GetViewportHeight()[2], 0);
	
	EXPECT_EQ(cam.GetOrigin(), Vec3({0,0,0}));


	EXPECT_EQ(cam.GetRay(0,0).origin(), origin);
	EXPECT_FLOAT_EQ(cam.GetRay(0,0).direction()[0], -1);
	EXPECT_FLOAT_EQ(cam.GetRay(0,0).direction()[1], -1);
	EXPECT_FLOAT_EQ(cam.GetRay(0,0).direction()[2], -1);

}

} // namespace artisan_gfx
