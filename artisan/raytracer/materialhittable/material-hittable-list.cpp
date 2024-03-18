#include "material-hittable-list.h"

namespace artisan_gfx {


MaterialHittableList::MaterialHittableList() {}
MaterialHittableList::MaterialHittableList(vector<shared_ptr<MaterialHittable>> initial_Material_hittables) {
	for (const auto& h : initial_Material_hittables) {
		this->Add(h);
	}
}

void MaterialHittableList::Add(shared_ptr<MaterialHittable> h) {
	Material_hittables.push_back(h);
}

void MaterialHittableList::Clear() {
	Material_hittables.clear(); 
}

MaybeMaterialHittable MaterialHittableList::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	HitRecord Material_hittable_rec;
	int hit_index = -1;
	for(int i = 0; i < Material_hittables.size(); i++) {
		const auto&h = Material_hittables[i];
		if ( h->Hit(r, t_min, t_max, Material_hittable_rec) ) {
			if(hit_index == -1) {
				hit_index = i;
				rec = Material_hittable_rec;
			}
			if(DistanceBetween(r.origin(),Material_hittable_rec.p) < DistanceBetween(r.origin(),rec.p)) {
				hit_index = i;
				rec = Material_hittable_rec;
			}
		}
	}
	if ( hit_index == -1 ) {
		return std::make_pair(false, shared_ptr<MaterialHittable>(nullptr));
	}
	return std::make_pair(true, Material_hittables[hit_index]);
}

} // namespace artisan_gfx
