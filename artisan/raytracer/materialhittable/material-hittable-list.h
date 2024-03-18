#include "material-hittable.h"

#include <memory>
#include <vector>

namespace artisan_gfx {

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::pair;

typedef pair<bool, shared_ptr<MaterialHittable>> MaybeMaterialHittable;

class MaterialHittableList {
	public:
		vector<shared_ptr<MaterialHittable>> Material_hittables;
		MaterialHittableList();
		MaterialHittableList(vector<shared_ptr<MaterialHittable>> initial_Material_hittables);
		void Add(shared_ptr<MaterialHittable> h);
		void Clear();
		MaybeMaterialHittable Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

} // namespace artisan_gfx
