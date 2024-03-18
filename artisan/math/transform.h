#pragma once 
#include "mat.h"
#include "vec.h"

namespace artisan_gfx {

Mat4 CameraTransform(Vec3 eye, Vec3 center, Vec3 up);

Mat4 ViewportTransform(double x_offset, double y_offset, double width, double height);

Vec3 Apply4DTransformToVector(Mat4& transform, Vec3& v);

Triangle3 Apply4DTransformToTriangle(Mat4& transform, Triangle3& t);

} // namespace artisan_gfx
