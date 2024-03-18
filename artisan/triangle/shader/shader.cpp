#include "artisan/triangle/shader/shader.h"

namespace artisan_gfx {

Mat<double, 2, 3> VertexUV(CTriangle& ct) {
	return Mat<double, 2, 3>({{
				{ct.GetA()["vt_u"], ct.GetB()["vt_u"], ct.GetC()["vt_u"]},
				{ct.GetA()["vt_v"], ct.GetB()["vt_v"], ct.GetC()["vt_v"]}
			}});
	
}

} // namespace artisan_gfx
