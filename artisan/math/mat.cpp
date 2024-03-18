#include "artisan/math/mat.h"

namespace artisan_gfx {

std::optional<Mat4> Mat4Inverse(Mat4 m) {
	Mat4 inv = identity<double, 4>();

	inv.SetRowMajor(0, m.RowMajor(5)  * m.RowMajor(10) * m.RowMajor(15) - 
		m.RowMajor(5)  * m.RowMajor(11) * m.RowMajor(14) - 
		m.RowMajor(9)  * m.RowMajor(6)  * m.RowMajor(15) + 
		m.RowMajor(9)  * m.RowMajor(7)  * m.RowMajor(14) +
		m.RowMajor(13) * m.RowMajor(6)  * m.RowMajor(11) - 
		m.RowMajor(13) * m.RowMajor(7)  * m.RowMajor(10));

	inv.SetRowMajor(4, -m.RowMajor(4)  * m.RowMajor(10) * m.RowMajor(15) + 
		m.RowMajor(4)  * m.RowMajor(11) * m.RowMajor(14) + 
		m.RowMajor(8)  * m.RowMajor(6)  * m.RowMajor(15) - 
		m.RowMajor(8)  * m.RowMajor(7)  * m.RowMajor(14) - 
		m.RowMajor(12) * m.RowMajor(6)  * m.RowMajor(11) + 
		m.RowMajor(12) * m.RowMajor(7)  * m.RowMajor(10));

	inv.SetRowMajor(8, m.RowMajor(4)  * m.RowMajor(9) * m.RowMajor(15) - 
		m.RowMajor(4)  * m.RowMajor(11) * m.RowMajor(13) - 
		m.RowMajor(8)  * m.RowMajor(5) * m.RowMajor(15) + 
		m.RowMajor(8)  * m.RowMajor(7) * m.RowMajor(13) + 
		m.RowMajor(12) * m.RowMajor(5) * m.RowMajor(11) - 
		m.RowMajor(12) * m.RowMajor(7) * m.RowMajor(9));

	inv.SetRowMajor(12, -m.RowMajor(4)  * m.RowMajor(9) * m.RowMajor(14) + 
		m.RowMajor(4)  * m.RowMajor(10) * m.RowMajor(13) +
		m.RowMajor(8)  * m.RowMajor(5) * m.RowMajor(14) - 
		m.RowMajor(8)  * m.RowMajor(6) * m.RowMajor(13) - 
		m.RowMajor(12) * m.RowMajor(5) * m.RowMajor(10) + 
		m.RowMajor(12) * m.RowMajor(6) * m.RowMajor(9));
	
	double det = m.RowMajor(0) * inv.RowMajor(0) + m.RowMajor(1) * inv.RowMajor(4) + m.RowMajor(2) * inv.RowMajor(8) + m.RowMajor(3) * inv.RowMajor(12);

	if (det == 0) {
		return std::nullopt;
	}

	inv.SetRowMajor(1, -m.RowMajor(1)  * m.RowMajor(10) * m.RowMajor(15) + 
		m.RowMajor(1)  * m.RowMajor(11) * m.RowMajor(14) + 
		m.RowMajor(9)  * m.RowMajor(2) * m.RowMajor(15) - 
		m.RowMajor(9)  * m.RowMajor(3) * m.RowMajor(14) - 
		m.RowMajor(13) * m.RowMajor(2) * m.RowMajor(11) + 
		m.RowMajor(13) * m.RowMajor(3) * m.RowMajor(10));

	inv.SetRowMajor(5, m.RowMajor(0)  * m.RowMajor(10) * m.RowMajor(15) - 
		m.RowMajor(0)  * m.RowMajor(11) * m.RowMajor(14) - 
		m.RowMajor(8)  * m.RowMajor(2) * m.RowMajor(15) + 
		m.RowMajor(8)  * m.RowMajor(3) * m.RowMajor(14) + 
		m.RowMajor(12) * m.RowMajor(2) * m.RowMajor(11) - 
		m.RowMajor(12) * m.RowMajor(3) * m.RowMajor(10));

	inv.SetRowMajor(9, -m.RowMajor(0)  * m.RowMajor(9) * m.RowMajor(15) + 
		m.RowMajor(0)  * m.RowMajor(11) * m.RowMajor(13) + 
		m.RowMajor(8)  * m.RowMajor(1) * m.RowMajor(15) - 
		m.RowMajor(8)  * m.RowMajor(3) * m.RowMajor(13) - 
		m.RowMajor(12) * m.RowMajor(1) * m.RowMajor(11) + 
		m.RowMajor(12) * m.RowMajor(3) * m.RowMajor(9));

	inv.SetRowMajor(13, m.RowMajor(0)  * m.RowMajor(9) * m.RowMajor(14) - 
		m.RowMajor(0)  * m.RowMajor(10) * m.RowMajor(13) - 
		m.RowMajor(8)  * m.RowMajor(1) * m.RowMajor(14) + 
		m.RowMajor(8)  * m.RowMajor(2) * m.RowMajor(13) + 
		m.RowMajor(12) * m.RowMajor(1) * m.RowMajor(10) - 
		m.RowMajor(12) * m.RowMajor(2) * m.RowMajor(9));

	inv.SetRowMajor(2, m.RowMajor(1)  * m.RowMajor(6) * m.RowMajor(15) - 
		m.RowMajor(1)  * m.RowMajor(7) * m.RowMajor(14) - 
		m.RowMajor(5)  * m.RowMajor(2) * m.RowMajor(15) + 
		m.RowMajor(5)  * m.RowMajor(3) * m.RowMajor(14) + 
		m.RowMajor(13) * m.RowMajor(2) * m.RowMajor(7) - 
		m.RowMajor(13) * m.RowMajor(3) * m.RowMajor(6));

	inv.SetRowMajor(6, -m.RowMajor(0)  * m.RowMajor(6) * m.RowMajor(15) + 
		m.RowMajor(0)  * m.RowMajor(7) * m.RowMajor(14) + 
		m.RowMajor(4)  * m.RowMajor(2) * m.RowMajor(15) - 
		m.RowMajor(4)  * m.RowMajor(3) * m.RowMajor(14) - 
		m.RowMajor(12) * m.RowMajor(2) * m.RowMajor(7) + 
		m.RowMajor(12) * m.RowMajor(3) * m.RowMajor(6));

	inv.SetRowMajor(10, m.RowMajor(0)  * m.RowMajor(5) * m.RowMajor(15) - 
		m.RowMajor(0)  * m.RowMajor(7) * m.RowMajor(13) - 
		m.RowMajor(4)  * m.RowMajor(1) * m.RowMajor(15) + 
		m.RowMajor(4)  * m.RowMajor(3) * m.RowMajor(13) + 
		m.RowMajor(12) * m.RowMajor(1) * m.RowMajor(7) - 
		m.RowMajor(12) * m.RowMajor(3) * m.RowMajor(5));

	inv.SetRowMajor(14, -m.RowMajor(0)  * m.RowMajor(5) * m.RowMajor(14) + 
		m.RowMajor(0)  * m.RowMajor(6) * m.RowMajor(13) + 
		m.RowMajor(4)  * m.RowMajor(1) * m.RowMajor(14) - 
		m.RowMajor(4)  * m.RowMajor(2) * m.RowMajor(13) - 
		m.RowMajor(12) * m.RowMajor(1) * m.RowMajor(6) + 
		m.RowMajor(12) * m.RowMajor(2) * m.RowMajor(5));

	inv.SetRowMajor(3, -m.RowMajor(1) * m.RowMajor(6) * m.RowMajor(11) + 
		m.RowMajor(1) * m.RowMajor(7) * m.RowMajor(10) + 
		m.RowMajor(5) * m.RowMajor(2) * m.RowMajor(11) - 
		m.RowMajor(5) * m.RowMajor(3) * m.RowMajor(10) - 
		m.RowMajor(9) * m.RowMajor(2) * m.RowMajor(7) + 
		m.RowMajor(9) * m.RowMajor(3) * m.RowMajor(6));

	inv.SetRowMajor(7, m.RowMajor(0) * m.RowMajor(6) * m.RowMajor(11) - 
		m.RowMajor(0) * m.RowMajor(7) * m.RowMajor(10) - 
		m.RowMajor(4) * m.RowMajor(2) * m.RowMajor(11) + 
		m.RowMajor(4) * m.RowMajor(3) * m.RowMajor(10) + 
		m.RowMajor(8) * m.RowMajor(2) * m.RowMajor(7) - 
		m.RowMajor(8) * m.RowMajor(3) * m.RowMajor(6));

	inv.SetRowMajor(11, -m.RowMajor(0) * m.RowMajor(5) * m.RowMajor(11) + 
		m.RowMajor(0) * m.RowMajor(7) * m.RowMajor(9) + 
		m.RowMajor(4) * m.RowMajor(1) * m.RowMajor(11) - 
		m.RowMajor(4) * m.RowMajor(3) * m.RowMajor(9) - 
		m.RowMajor(8) * m.RowMajor(1) * m.RowMajor(7) + 
		m.RowMajor(8) * m.RowMajor(3) * m.RowMajor(5));

	inv.SetRowMajor(15, m.RowMajor(0) * m.RowMajor(5) * m.RowMajor(10) - 
		m.RowMajor(0) * m.RowMajor(6) * m.RowMajor(9) - 
		m.RowMajor(4) * m.RowMajor(1) * m.RowMajor(10) + 
		m.RowMajor(4) * m.RowMajor(2) * m.RowMajor(9) + 
		m.RowMajor(8) * m.RowMajor(1) * m.RowMajor(6) - 
		m.RowMajor(8) * m.RowMajor(2) * m.RowMajor(5));

	return inv / det;
}

} // namespace artisan_gfx
