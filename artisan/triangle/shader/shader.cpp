#include "artisan/triangle/shader/shader.h"

namespace artisan_gfx {

Mat<double, 2, 3> VertexUV(CTriangle& ct) {
	return Mat<double, 2, 3>({{
				{ct.GetA()["vt_u"], ct.GetB()["vt_u"], ct.GetC()["vt_u"]},
				{ct.GetA()["vt_v"], ct.GetB()["vt_v"], ct.GetC()["vt_v"]}
			}});
	
}

Mat<double, 3, 3> VertexNormal(CTriangle& ct) {
	return Mat<double, 3, 3>({{
				{ct.GetA()["vn_x"], ct.GetB()["vn_x"], ct.GetC()["vn_x"]},
				{ct.GetA()["vn_y"], ct.GetB()["vn_y"], ct.GetC()["vn_y"]},
				{ct.GetA()["vn_z"], ct.GetB()["vn_z"], ct.GetC()["vn_z"]}
			}});
	
}

} // namespace artisan_gfx
