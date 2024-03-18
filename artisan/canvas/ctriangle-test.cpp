#include "gtest/gtest.h"
#include "ctriangle.h"
#include "cvertex.h"

namespace artisan_gfx {

TEST(CTriangleTest, GetPoints) {
	Triangle3 t = Triangle3(
		Vertex3({0,1, .1}),
		Vertex3({2,3, .2}),
		Vertex3({4,5, .3}));

	CTriangle ct = CTriangle(t);

	EXPECT_EQ(ct.GetA()[0], 0);
	EXPECT_EQ(ct.GetA()[1], 1);
	EXPECT_EQ(ct.GetA().z, .1);
	EXPECT_EQ(ct.GetB()[0], 2);
	EXPECT_EQ(ct.GetB()[1], 3);
	EXPECT_EQ(ct.GetB().z, .2);
	EXPECT_EQ(ct.GetC()[0], 4);
	EXPECT_EQ(ct.GetC()[1], 5);
	EXPECT_EQ(ct.GetC().z, .3);
}

TEST(CTriangleTest, BoundingBox) {
	Triangle3 t = Triangle3(
		Vertex3({0,0, .1}),
		Vertex3({1,1, .2}),
		Vertex3({2,2, .3}));


	CTriangle ct = CTriangle(t);

	BoundingBox b = BoundingBoxOf(ct);

	EXPECT_EQ(b.top_left[0], 0);
	EXPECT_EQ(b.top_left[1], 0);
	EXPECT_EQ(b.bottom_right[0], 2);
	EXPECT_EQ(b.bottom_right[1], 2);
}

} // namespace artisan_gfx
