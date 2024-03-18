#include "cpoint.h"

namespace artisan_gfx {

bool operator==(const cpoint u, const cpoint v) {
	return (u.cords == v.cords) && (u.z == v.z);
}

cpoint operator+(const cpoint u, const cpoint v) {
	return cpoint(u.cords + v.cords, u.z + v.z);
}


cpoint operator-(const cpoint u, const cpoint v) {
	return cpoint(u.cords - v.cords, u.z - v.z);
}

} // namespace artisan_gfx
