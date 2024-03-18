#include <memory>
#include "artisan/raytracer/geometry/hittable.h"
#include "artisan/raytracer/material/material.h"

namespace artisan_gfx {

using std::shared_ptr;

class MaterialHittable : public Hittable {
		shared_ptr<Material> mtrl;
		shared_ptr<Hittable> htbl;
public:
		MaterialHittable();
		MaterialHittable(shared_ptr<Material> m, shared_ptr<Hittable> h);
		virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec)
			const override;
		bool Scatter(const Ray& r, const HitRecord& hr, scatter_record& sr) const;
};

} // namespace artisan_gfx
