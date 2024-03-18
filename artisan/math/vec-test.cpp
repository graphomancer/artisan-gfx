#include "gtest/gtest.h"
#include "vec.h"

namespace artisan_gfx {

TEST(VecgTest, VecOfVec) {
	Vec<Vec<int,2>,2> m2 = Vec<Vec<int,2>,2>({
				Vec<int,2>({-1,-2}),
				Vec<int,2>({-3,-4})
		      	});
	EXPECT_EQ(m2[0][0] , -1);
	EXPECT_EQ(m2[0][1] , -2);
	EXPECT_EQ(m2[1][0] , -3);
	EXPECT_EQ(m2[1][1] , -4);
	EXPECT_EQ(m2[0] * m2[1], 11);
}

TEST(VecgTest, TestNegation) {
	Vec<int, 3> a = Vec<int,3>({1,2,3});
	Vec<int, 3> minusa = Vec<int,3>({-1,-2,-3});
	EXPECT_EQ(-a, minusa);
}

TEST(VecgTest, TestSum) {
	Vec<int, 3> a = Vec<int,3>({1,2,3});
	Vec<int, 3> twoa = Vec<int,3>({2,4,6});
	EXPECT_EQ(a + a, twoa);
}

TEST(VecgTest, TestDiff) {
	Vec<int, 3> a = Vec<int,3>({1,2,3});
	Vec<int, 3> b = Vec<int,3>({1,1,5});
	Vec<int, 3> diff = Vec<int,3>({0,1,-2});
	EXPECT_EQ(a - b, diff);
}

TEST(VecgTest, TestProduct) {
	Vec<int, 3> a = Vec<int,3>({1,2,3});
	int s = 2;
	Vec<int, 3> prod = Vec<int,3>({2,4,6});
	EXPECT_EQ(a * s, prod);
	EXPECT_EQ(s * a, prod);
}

TEST(VecgTest, TestQuotient) {
	Vec<int, 3> prod = Vec<int,3>({2,4,6});
	int q = 2;
	Vec<int, 3> a = Vec<int,3>({1,2,3});
	EXPECT_EQ(prod / q, a);
}

TEST(VecgTest, TestDot) {
	Vec<int, 3> a = Vec<int,3>({1,2,3});
	Vec<int, 3> b = Vec<int,3>({0,4,7});
	EXPECT_EQ(a * b, 29);
}

TEST(VecgTest, TestMagnitude) {
	Vec<int,3> evec = Vec<int,3>({0,3,4});
	EXPECT_EQ(evec.MagnitudeSquared(), 25);
	EXPECT_EQ(Magnitude(evec), 5.0);
}

TEST(VecgTest, TestAssignment) {
	Vec<int, 3> a = Vec<int,3>({1,2,3});
	a[0] = 2;
	EXPECT_EQ(a[0], 2);
}

TEST(VecgTest, TestDistance) {
	Vec<int,2> evec = Vec<int,2>({3,4});
	Vec<int,2> origin = Vec<int,2>({0,0});
	EXPECT_EQ(DistanceBetween(evec, origin), 5.0);
}

} // namespace artisan_gfx
