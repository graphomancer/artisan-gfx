#pragma once

#include <utility>
#include <algorithm>
#include "artisan/triangle/triangle.h"
#include "artisan/canvas/cvertex.h"
#include "artisan/math/vec3.h"
#include "artisan/math/vec.h"

namespace artisan_gfx {

const Vec3 DEGENERATE_BARYCENTRIC_COORDINATES = Vec3({-1, -1, -1});

typedef struct {
	Vec<int, 2> top_left;
	Vec<int, 2> bottom_right;
} BoundingBox;

class CTriangle : public Triangle<CVertex> {
public:
	CTriangle(Triangle3& t3) : Triangle<CVertex>(t3.GetA(), t3.GetB(), t3.GetC()) {};
};


Vec3 BarycentricCords(Vec<int, 2>& p, CTriangle& triangle);

bool BarycentricIsInternal(Vec3& bary);

BoundingBox BoundingBoxOf(CTriangle& t);

} // namespace artisan_gfx
