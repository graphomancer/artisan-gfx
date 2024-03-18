#pragma once

namespace artisan_gfx {

const double pi = 3.1415926535897932385;
inline const double DegreesToRadians(double degrees) {
	return degrees * pi / 180.0;
}

} // namespace artisan_gfx
