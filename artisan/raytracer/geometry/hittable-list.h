#include "hittable.h"

#include <memory>
#include <vector>

namespace artisan_gfx {

using std::shared_ptr;
using std::make_shared;
using std::vector;

class HittableList : public Hittable {
		vector<shared_ptr<Hittable>> hittables;
	public:
		HittableList();
		HittableList(vector<shared_ptr<Hittable>> initial_hittables);
		void Add(shared_ptr<Hittable> h);
		void Clear();
		virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace artisan_gfx
