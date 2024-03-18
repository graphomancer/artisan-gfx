#include "vec4.h"

namespace artisan_gfx {

Vec4 ToHomogeneousPoint(Vec3& v) {
	return Vec4({v[0], v[1], v[2], 1});
}

Vec3 FromHomogeneousPoint(Vec4& v) {
	return Vec3({ v[0], v[1], v[2]}) / v[3];
}

Vec4 ToHomogeneousVector(Vec3& v) {
	return Vec4({v[0], v[1], v[2], 0});
}

Vec3 FromHomogeneousVector(Vec4& v) {
	return Vec3({ v[0], v[1], v[2]}); 
}

} // namespace artisan_gfx
