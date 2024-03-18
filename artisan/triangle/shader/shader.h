#pragma once
#include "artisan/triangle/triangle.h"
#include "artisan/math/mat.h"
#include "artisan/math/vec3.h"
#include "artisan/file/tga.h"
#include "artisan/canvas/ctriangle.h"

namespace artisan_gfx {

Triangle3 Apply4DTransform(Mat4 &transform, Triangle3 &triangle);

Mat<double, 2, 3> VertexUV(CTriangle& ct);

Mat<double, 3, 3> VertexNormal(CTriangle& ct);

class Shader {
public:
	virtual Triangle3 Vertex(Triangle3 &t) = 0;
	virtual Color Fragment(const Vec3 &barycentric_cords, CTriangle &t) = 0;
	Shader() {}
};

} // namespace artisan_gfx
