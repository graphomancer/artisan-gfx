#include "gtest/gtest.h"
#include "mat.h"

namespace artisan_gfx {

TEST(MatTest, GetOperator) {
	Mat<int,2,2> m = Mat<int,2,2>({{
				{1,2},
				{3,4}
			}});
	EXPECT_EQ(m[0] * m[1], 11);
}

TEST(MatTest, TestVectorMul) {
	Mat<int,3,2> m = Mat<int,3,2>({{
				{1,2},
				{3,4},
				{5,6}
			}});
	Vec<int,2> v = Vec<int,2>({-1,-1});
	Vec<int,3> prod = m * v;

	EXPECT_EQ(prod[0], -3);
	EXPECT_EQ(prod[1], -7);
	EXPECT_EQ(prod[2], -11);
}

TEST(MatTest, TestTranspose) {
	Mat<int,3,2> m = Mat<int,3,2>({{
				{1,2},
				{3,4},
				{5,6}
			}});
	Mat<int,2,3> trans = m.transpose();
	EXPECT_EQ(trans[0][0],1);
	EXPECT_EQ(trans[0][1],3);
	EXPECT_EQ(trans[0][2],5);

	EXPECT_EQ(trans[1][0],2);
	EXPECT_EQ(trans[1][1],4);
	EXPECT_EQ(trans[1][2],6);
}

TEST(MatTest, TestMul) {
	Mat<int,2,3> a = Mat<int,2,3>({{
				{1, 2, 3},
				{4, 5, 6}
			}});
	Mat<int,3,2> b = Mat<int,3,2>({{
				{7,8},
				{9,10},
				{11,12}
			}});
	Mat<int, 2,2> c = a * b;
	Mat<int, 2,2> expected = Mat<int,2,2>({{
				{58, 64},
				{139, 154}
			}});
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			EXPECT_EQ(c[i][j], expected[i][j]);
		}
	}
}

TEST(MatTest, TestMulTriangle) {
	Vec<int,3> A = Vec<int,3>({1,2,3});
	Vec<int,3> B = Vec<int,3>({2,3,4});
	Vec<int,3> C = Vec<int,3>({4,5,6});
	Triangle<Vertex<int,3>> t = Triangle<Vertex<int,3>>(A, B, C);
	Mat<int, 3, 3> negIdent = Mat<int,3,3>({{
				{-1,0,0},
				{0,-1,0},
				{0,0,-1},
			}});
	Triangle<Vertex<int,3>> negT = negIdent * t;

	for(int i = 0; i < 2; i++) {
		EXPECT_EQ(negT.GetA()[i], -1 * t.GetA()[i]);
		EXPECT_EQ(negT.GetB()[i], -1 * t.GetB()[i]);
		EXPECT_EQ(negT.GetC()[i], -1 * t.GetC()[i]);
	}
}

TEST(MatTest, TestAssignment) {
	Mat<double,4,4> matrix = Mat<double, 4, 4>({{
				{1,0,0,0},
				{0,1,0,0},
				{0,0,1,0},
				{0,0, 0, 1}
			}});
	matrix[0][0] = 50;
	EXPECT_EQ(matrix[0][0], 50);
}

TEST(MatTest, TestProjection) {
	double r = -1/3;
	Mat<double,4,4> projection = Mat<double, 4, 4>({{
				{1,0,0,0},
				{0,1,0,0},
				{0,0,1,0},
				{0,0, r, 1}
			}});

	Vec3 A = Vec3({1,2,3});
	Vec3 B = Vec3({2,3,4});
	Vec3 C = Vec3({4,5,5});
	Triangle3 t = Triangle3(A, B, C);

	Triangle4 holoT = projection * ToHomogeneousTriangle(t);
	Triangle3 projT = FromHomogeneousTriangle(holoT);

	EXPECT_DOUBLE_EQ(holoT.GetA()[3], 1 + r * t.GetA()[2]);

	for(int i = 0; i < 2; i++) {
		EXPECT_DOUBLE_EQ(projT.GetA()[i], 1/(r * t.GetA()[2] + 1)  * t.GetA()[i]);
		EXPECT_DOUBLE_EQ(projT.GetB()[i], 1/(r * t.GetB()[2] + 1)   * t.GetB()[i]);
		EXPECT_DOUBLE_EQ(projT.GetC()[i], 1/(r * t.GetC()[2] + 1)   * t.GetC()[i]);
	}

}

TEST(MatTest, TestIdentity) {
	Mat<int,4,4> id = identity<int,4>();
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if (i != j) {
				EXPECT_EQ(id[i][j], 0);
			} else {
				EXPECT_EQ(id[i][j], 1);
			}
		}
	}
}

TEST(MatTest, Mat4Inverse) {
	Mat<double,4,4> got = Mat<double, 4, 4>({{
				{5, 6, 6, 8},
				{2, 2, 2, 8},
				{6, 6, 2, 8},
				{2, 3, 6, 7},
			}});
	Mat<double,4,4> want = Mat<double, 4, 4>({{
				{-17, -9, 12, 16},
				{17, 8.75, -11.75, -16},
				{-4, -2.25, 2.75, 4},
				{1, .75, -.75, -1},
			}});
	Mat4 inv = Mat4Inverse(got).value();
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			EXPECT_EQ(inv[i][j], want[i][j]);
		}
	}

}

TEST(MatTest, SetTest) {
	Mat4 m = identity<double, 4>();
	m[0][0] = 100;
	EXPECT_EQ(m[0][0], 100);
}

TEST(MatTest, SetRowMajorTest) {
	Mat4 m = identity<double, 4>();
	m.SetRowMajor(0, 100);
	EXPECT_EQ(m[0][0], 100);
}

} // namespace artisan_gfx
