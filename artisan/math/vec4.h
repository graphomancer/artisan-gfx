#pragma once
#include "vec.h"
#include "vec3.h"

namespace artisan_gfx {

typedef Vec<double, 4> Vec4;

Vec4 ToHomogeneousPoint(Vec3& v);

Vec3 FromHomogeneousPoint(Vec4& v);

Vec4 ToHomogeneousVector(Vec3& v);

Vec3 FromHomogeneousVector(Vec4& v);

} // namespace artisan_gfx
