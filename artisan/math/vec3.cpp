#include <cmath>
#include "vec3.h"
#include "stats.h"

namespace artisan_gfx {

using std::sqrt;


Vec3 Cross(const Vec3& u, const Vec3& v) {
	return Vec3({
		u[1] * v[2] - u[2] * v[1],
		u[2] * v[0] - u[0] * v[2],
		u[0] * v[1] - u[1] * v[0]
	});
}

Vec3 RandomVector(double min, double max) {
	return Vec3({
		RandomDouble(min, max),
		RandomDouble(min, max),
		RandomDouble(min, max)
	});
}

// refactor this laziness to not be recursive
Vec3 RandomVectorInUnitSphere() {
	while (true) {
		Vec3 random = RandomVector(-1, 1);
		if (Magnitude(random) < 1) {
			return random;
		}
	}
}

Vec3 MultiplyVectorElements(const Vec3& u, const Vec3& v) {
	return Vec3({
		u[0] * v[0],
		u[1] * v[1],
		u[2] * v[2]
	});
}

} // namespace artisan_gfx
