#include "gtest/gtest.h"
#include "artisan/canvas/cvertex.h"

namespace artisan_gfx {

TEST(CVertexTest, Initialization) {
	Vertex3 v({1.0, 2.0, 3.0});
	CVertex cv = CVertex(v);

	EXPECT_EQ(cv[0], 1);
	EXPECT_EQ(cv[1], 2);
	EXPECT_EQ(cv.z, 3.0);
}

} // namespace artisan_gfx
