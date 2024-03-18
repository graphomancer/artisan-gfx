#include "hittable-list.h"

namespace artisan_gfx {


HittableList::HittableList() {}
HittableList::HittableList(vector<shared_ptr<Hittable>> initial_hittables) {
	for (const auto& h : initial_hittables) {
		this->Add(h);
	}
}

void HittableList::Add(shared_ptr<Hittable> h) {
	hittables.push_back(h);
}

void HittableList::Clear() {
	hittables.clear();
}

bool HittableList::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	HitRecord hittable_rec;
	bool something_hit = false;

	for(const auto& h : hittables) {
		if ( h->Hit(r, t_min, t_max, hittable_rec) ) {
			if( !something_hit ) {
				something_hit = true;
				rec = hittable_rec;
			}
			if(DistanceBetween(r.origin(), hittable_rec.p) < DistanceBetween(r.origin(),rec.p)) {
				rec = hittable_rec;
			}
		}
	}
	return something_hit;
}

} // namespace artisan_gfx
