#include "gtest/gtest.h"
#include "triangle.h"
#include <utility>

namespace artisan_gfx {

using namespace std;

TEST(TriangleTest, GetVertexPairs) {
	Vertex3 A = Vertex3({1,2,3});
	Vertex3 B = Vertex3({2,3,4});
	Vertex3 C = Vertex3({4,5,6});
	Triangle3 t = Triangle3(A, B, C);
	std::vector<std::pair<Vertex3, Vertex3>> pairs = t.GetVertexPairs();

	EXPECT_EQ(pairs.size(), 3);
	EXPECT_EQ(pairs[0], std::make_pair( t.GetA(), t.GetB()));
	EXPECT_EQ(pairs[1], std::make_pair( t.GetA(), t.GetC()));
	EXPECT_EQ(pairs[2], std::make_pair( t.GetB(), t.GetC()));
}



TEST(TriangleTest, GetVerticiesByY) {
	Vertex3 XXX = Vertex3({0,3,0});
	Vertex3 XX = Vertex3({0,2,0});
	Vertex3 X = Vertex3({0,1,0});

	vector<Triangle3> tlist;

	tlist.push_back(Triangle3(XXX,XX,X));
	tlist.push_back(Triangle3(XXX,X,XX));
	tlist.push_back(Triangle3(XX,XXX,X));
	tlist.push_back(Triangle3(XX,X,XXX));
	tlist.push_back(Triangle3(X,XX,XXX));
	tlist.push_back(Triangle3(X,XXX,XX));

	vector<Vertex3> sortedVerticies;

	sortedVerticies.push_back(XXX);
	sortedVerticies.push_back(XX);
	sortedVerticies.push_back(X);

	for(unsigned int i = 0; i < tlist.size(); i++) {
		EXPECT_EQ(tlist[i].GetVerticiesByY(), sortedVerticies);
	}
}

TEST(TriangleTest, ToHomogeneous) {
	Vertex3 XXX = Vertex3({0,3,0});
	Vertex3 XX = Vertex3({0,2,0});
	Vertex3 X = Vertex3({0,1,0});

	Triangle3 t = Triangle3(X, XX, XXX);
	Triangle4 h = ToHomogeneousTriangle(t);
	for(unsigned int i = 0; i < 3; i++) {
		EXPECT_EQ(h.GetA()[i], X[i]);
		EXPECT_EQ(h.GetB()[i], XX[i]);
		EXPECT_EQ(h.GetC()[i], XXX[i]);
	}
	EXPECT_EQ(h.GetA()[3], 1);
	EXPECT_EQ(h.GetB()[3], 1);
	EXPECT_EQ(h.GetC()[3], 1);
}

} // namespace artisan_gfx
