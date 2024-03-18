#include "gtest/gtest.h"
#include "vertex.h"
#include <utility>

namespace artisan_gfx {

TEST(VertexTest, Equality) {
	Vertex3 v(
		Vec<double, 3>({1.5, 2.5, 3.5}),
		Properties()
	);
	v["prop"] = 2.5;
	
	Vertex3 u(
		Vec<double, 3>({1.5, 2.5, 3.5}),
		Properties()
	);
	u["prop"] = 2.5;

	Vertex3 unequalCords(
		Vec<double, 3>({.5, 2.5, 3.5}),
		Properties()
	);
	unequalCords["prop"] = 2.5;

	Vertex3 unequalProps(
		Vec<double, 3>({1.5, 2.5, 3.5}),
		Properties()
	);
	unequalProps["prop"] = .5;

	EXPECT_EQ(u,v);
	EXPECT_NE(u,unequalCords);
	EXPECT_NE(u,unequalProps);
}

TEST(VertexTest, Homogeneous) {
	Vertex<double, 3> v(
		Vec<double, 3>({1.5, 2.5, 3.5}),
		Properties()
	);
	v["prop"] = 2.5;

	Vertex4 h = ToHomogeneousVertex(v);
	EXPECT_EQ(h[0], 1.5);
	EXPECT_EQ(h[1], 2.5);
	EXPECT_EQ(h[2], 3.5);
	EXPECT_EQ(h[3], 1);
	EXPECT_EQ(h["prop"], 2.5);

	h[3] = .5;

	Vertex3 unH = FromHomogeneousVertex(h);
	EXPECT_EQ(unH[0], 3);
	EXPECT_EQ(unH[1], 5);
	EXPECT_EQ(unH[2], 7);
	EXPECT_EQ(unH["prop"], 2.5);
	
}

TEST(VertexTest, Constructor) {
	Vertex<double, 3> v(
		Vec<double, 3>({1.5, 2.5, 3.5}),
		Properties()
	);
	v["prop"] = 2.5;
	EXPECT_EQ(v[0], 1.5);
	EXPECT_EQ(v[1], 2.5);
	EXPECT_EQ(v[2], 3.5);
	EXPECT_EQ(v["prop"], 2.5);

}

TEST(VertexTest, GetCords) {
	Vertex<double, 3> v(
		Vec<double, 3>({1.5, 2.5, 3.5}),
		Properties()
	);

	Vec<double, 3> c = v.GetCords();
	c[0] = 50;
	EXPECT_EQ(c[0], 50);
	EXPECT_EQ(c[1], 2.5);
	EXPECT_EQ(c[2], 3.5);

	EXPECT_EQ(v[0], 1.5);
	EXPECT_EQ(v[1], 2.5);
	EXPECT_EQ(v[2], 3.5);
}


TEST(VertexTest, GetSetCords) {
	Vertex<double, 3> v;
	v[0] = 1.5;
	v[1] = 2.5;
	v[2] = 3.5;

	EXPECT_EQ(v[0], 1.5);
	EXPECT_EQ(v[1], 2.5);
	EXPECT_EQ(v[2], 3.5);
}

TEST(VertexTest, GetSetProps) {
	Vertex<double, 3> v;
	v["prop"] = 2.5;
	EXPECT_EQ(v["prop"], 2.5);
}

} // namespace artisan_gfx
