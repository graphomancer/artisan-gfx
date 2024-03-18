#pragma once 
#include "vec.h"

namespace artisan_gfx {

typedef Vec<double, 3> Vec3;

Vec3 Cross(const Vec3& u, const Vec3& v);
Vec3 RandomVector(double min, double max);
Vec3 RandomVectorInUnitSphere(); 
Vec3 MultiplyVectorElements(const Vec3& u, const Vec3& v);

using Point3 = Vec3;
using Color = Vec3;

} // namespace artisan_gfx
