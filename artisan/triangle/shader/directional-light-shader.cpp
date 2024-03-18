#include "artisan/triangle/shader/directional-light-shader.h"
#include "artisan/triangle/shader/shader.h"
#include "artisan/math/transform.h"

namespace artisan_gfx {

	DirectionalLightShader::DirectionalLightShader(Mat4 viewport, Mat4 projection, Mat4 camera, Vec3 light_dir,
			TGA diffuse_texture, TGANormalmap normalmap) :
						diffuse_texture_(diffuse_texture),
						normalmap_(normalmap) {
		projection_camera_transform_ = projection * camera;
		projection_camera_inverse_transform_ = Mat4Inverse(projection_camera_transform_).value().transpose();
		viewport_projection_camera_transform_ = viewport * projection_camera_transform_;
		light_dir_ = Normalize(Apply4DTransformToVector(camera, light_dir));
	}
	

Triangle3 DirectionalLightShader::Vertex(Triangle3 &t) {
	return Apply4DTransformToTriangle(viewport_projection_camera_transform_, t);
}

Color DirectionalLightShader::Fragment(const Vec3& barycentric_cords, CTriangle& t) {
	Vec2 uv = VertexUV(t) * barycentric_cords;
	Vec3 normal = normalmap_.getUV(uv);
	normal = Normalize(Apply4DTransformToVector(
				projection_camera_inverse_transform_, normal));
	Vec3 reflection_dir = Normalize(normal * (normal * light_dir_ * 2) - light_dir_);
	float diffuse_coefficient = std::max(0.0d, normal * light_dir_);
	Color base_color = RGBAToVec3(diffuse_texture_.getUV(uv));

	for(int i = 0; i < 3; i++) {
		base_color[i] =std::min<double>(5. + base_color[i] * (diffuse_coefficient), 255);
	}

	return base_color;
}

} // namespace artisan_gfx
