#include "sphere.h"
#include <iostream>

namespace artisan_gfx {

Sphere::Sphere() = default;
Sphere::Sphere(const Point3& center, const double radius) : center(center), radius(radius) {}

/*

P(t) = A + tb
(P(t) - C) * (P(t) - c) = r^2
(A - C + tb) * (A - C + tb) = r^2
(A - C) * (A - C) + t^2 b * b - 2t * (A - C) * b - r^2 = 0

quadratic formula:

-Bq +/- sqrt(Aq^2 - 4AqCq)
----------------------
          2Aq

Aq = b * b
Bq = 2 * (A - C) * b
Cq = (A - C) * (A - C) - r^2


intersects if discriminant is >= 0, at points A + bt where t are the roots


*/
bool Sphere::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {

    double A = r.direction() * r.direction();
    double B = 2. * (r.origin() - center) * r.direction();
    double C = (r.origin() - center) * (r.origin() - center) - radius * radius;
    double discriminant = B * B - 4 * A * C;
    bool hit = discriminant > 0;
    if (!hit) {
        return false;
    }

    double t_0 = (-B - sqrt(discriminant)) / (2 * A);
    double t_1 = (-B + sqrt(discriminant)) / (2 * A);
    if ( t_0 < 0 && t_1 < 0 ) {
	    // Sphere is behind the ray
	    return false;
    }
    double t_hit = t_0 < 0 ? t_1: t_0;
    // invert normal if Ray is inside sphere
    double normal_multiplier = t_0 < 0 ? -1: 1; 

    if (t_hit < t_min || t_hit > t_max) {
	    return false;
    }

    rec.p = r.at(t_hit);
    rec.normal = (normal_multiplier * (rec.p - center) / radius);
    
    return true;
}

} // namespace artisan_gfx
