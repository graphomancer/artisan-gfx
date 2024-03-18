#include "artisan/triangle/shader/simple-tga-shader.h"
#include "artisan/triangle/shader/shader.h"
#include "artisan/math/transform.h"

namespace artisan_gfx {

Triangle3 SimpleTGAShader::Vertex(Triangle3 &t) {
	return Apply4DTransformToTriangle(viewport_projection_camera_transform_, t);
}

Color SimpleTGAShader::Fragment(const Vec3 &barycentric_cords, CTriangle &t) {
	return RGBAToVec3(tga_.getUV(VertexUV(t) * barycentric_cords));
}

} // namespace artisan_gfx
