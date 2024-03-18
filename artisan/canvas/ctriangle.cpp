#include "ctriangle.h"

namespace artisan_gfx {

Vec3 BarycentricCords(Vec<int, 2>& p, CTriangle& triangle) {
	Vec3 x_vector = Vec3({
			double(triangle.GetB()[0] - triangle.GetA()[0]),
		       	double(triangle.GetC()[0] - triangle.GetA()[0]),
		       	double(triangle.GetA()[0] - p[0])});
	Vec3 y_vector = Vec3({
			double(triangle.GetB()[1] - triangle.GetA()[1]),
		       	double(triangle.GetC()[1] - triangle.GetA()[1]),
		       	double(triangle.GetA()[1] - p[1])});
	
	Vec3 cross_product = Cross(x_vector, y_vector);
	if (cross_product[2] == 0) {
		return DEGENERATE_BARYCENTRIC_COORDINATES;
	}
	Vec3 normalized_cross_product = cross_product / cross_product[2];
	return Vec3({
			1 - (normalized_cross_product[0] + normalized_cross_product[1]),
			normalized_cross_product[0],
			normalized_cross_product[1]
		});
}

bool BarycentricIsInternal(Vec3& bary) {
	return 0 <= bary[0]  && bary[0] <= 1 &&
		0 <= bary[1] && bary[1] <= 1 &&
		0 <= bary[2] && bary[2] <= 1;
}

BoundingBox BoundingBoxOf(CTriangle& t) {
	BoundingBox box;
	box.top_left[0] = std::min({t.GetA()[0], t.GetB()[0], t.GetC()[0]});
	box.top_left[1] = std::min({t.GetA()[1], t.GetB()[1], t.GetC()[1]});
	box.bottom_right[0] = std::max({t.GetA()[0], t.GetB()[0], t.GetC()[0]});
	box.bottom_right[1] = std::max({t.GetA()[1], t.GetB()[1], t.GetC()[1]});
	return box;
}

} // namespace artisan_gfx
