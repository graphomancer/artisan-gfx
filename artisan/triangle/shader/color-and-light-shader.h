#include "artisan/triangle/shader/shader.h"
#include "artisan/math/vec2.h"

namespace artisan_gfx {

class ColorAndLightShader: public Shader {
	Mat4 viewport_projection_camera_transform_;
	Mat4 projection_camera_transform_;
	Mat4 projection_camera_inverse_transform_;
	Vec3 light_dir_;
	Color base_color_;
public:
	ColorAndLightShader(Mat4 viewport, Mat4 projection, Mat4 camera, Vec3 light_dir, Color base_color);
	Triangle3 Vertex(Triangle3 &t) override;
	Color Fragment(const Vec3 &barycentric_cords, CTriangle &t) override;
};

} // namespace artisan_gfx
