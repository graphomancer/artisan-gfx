#include "gtest/gtest.h"
#include "ctriangle.h"
#include "cpoint.h"

namespace artisan_gfx {

TEST(CpointTest, assignment) {
	cpoint A = cpoint({0,0}, 1.0);
	A[1] = 1;
	EXPECT_EQ(A[1], 1);
}

} // namespace artisan_gfx
