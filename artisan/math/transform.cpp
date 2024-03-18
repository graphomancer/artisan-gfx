#include "transform.h"
#include "mat.h"
#include "vec.h"

namespace artisan_gfx {

Mat4 CameraTransform(Vec3 eye, Vec3 center, Vec3 up) {
	Vec3 z = Normalize(eye - center);
	Vec3 x = Normalize(Cross(up,z));
	Vec3 y = Normalize(Cross(z,x));

	Mat4 basis_conversion = identity<double,4>();
	Mat4 shift_to_eye = identity<double,4>();

	for(int i = 0; i < 3; i++) {
		basis_conversion[0][i] = x[i];
		basis_conversion[1][i] = y[i];
		basis_conversion[2][i] = z[i];

		shift_to_eye[i][3] = -eye[i];
	}
	return basis_conversion * shift_to_eye;
}

Mat4 ViewportTransform(double x_offset, double y_offset, double width, double height) {
	Mat4 transform = Mat4({{
		{width/2., 0, 0, x_offset + width/2.},
		{0, height/2., 0, y_offset + height/2.},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}});
	return transform;
}

Vec3 Apply4DTransformToVector(Mat4& transform, Vec3& v) {
	Vec4 hv = transform * ToHomogeneousVector(v);
	return FromHomogeneousVector(hv);
}


Triangle3 Apply4DTransformToTriangle(Mat4& transform, Triangle3& t) {
	return FromHomogeneousTriangle(transform * ToHomogeneousTriangle(t));
}

} // namespace artisan_gfx
