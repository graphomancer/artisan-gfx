#include "artisan/triangle/shader/shader.h"
#include "artisan/math/vec2.h"

namespace artisan_gfx {

class DirectionalLightShader: public Shader {
	Mat4 viewport_projection_camera_transform_;
	Mat4 projection_camera_transform_;
	Mat4 projection_camera_inverse_transform_;
	Vec3 light_dir_;
	TGA diffuse_texture_;
	TGANormalmap normalmap_;
public:
	DirectionalLightShader(Mat4 viewport, Mat4 projection, Mat4 camera, Vec3 light_dir,
			TGA diffuse_texture, TGANormalmap normalmap);
	Triangle3 Vertex(Triangle3 &t) override;
	Color Fragment(const Vec3 &barycentric_cords, CTriangle &t) override;
};

} // namespace artisan_gfx
