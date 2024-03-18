#include "artisan/triangle/shader/shader.h"

namespace artisan_gfx {

class SimpleTGAShader : public Shader {
	Mat4 viewport_projection_camera_transform_;
	TGA tga_;
public:
	SimpleTGAShader(Mat4 transform , TGA tga) : viewport_projection_camera_transform_(transform), tga_(tga) {}
	Triangle3 Vertex(Triangle3 &t) override;
	Color Fragment(const Vec3 &barycentric_cords, CTriangle &t) override;
};

} // namespace artisan_gfx
