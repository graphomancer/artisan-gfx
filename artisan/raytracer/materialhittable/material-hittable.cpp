#include "material-hittable.h"

namespace artisan_gfx {

MaterialHittable::MaterialHittable() {}
MaterialHittable::MaterialHittable(shared_ptr<Material> m, shared_ptr<Hittable> h) :
	mtrl(m), htbl(h) {}

bool MaterialHittable::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	return htbl->Hit(r, t_min, t_max, rec);
}

bool MaterialHittable::Scatter(const Ray& r, const HitRecord& hr, scatter_record& sr) const {
	return mtrl->Scatter(r, hr, sr);
}

} // namespace artisan_gfx
