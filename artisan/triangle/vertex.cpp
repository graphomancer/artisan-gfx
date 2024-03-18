#include "vertex.h"

namespace artisan_gfx {

Vertex4 ToHomogeneousVertex(Vertex3 v) {
	Vec<double, 3> currentCords = v.GetCords();
	return Vertex<double, 4>(
		Vec<double, 4>({
			currentCords[0],
			currentCords[1],
			currentCords[2],
			1,
		}),
		v.GetProperties()
	);
}

Vertex3 FromHomogeneousVertex(Vertex4 v) {
	Vec<double, 4> currentCords = v.GetCords();
	return Vertex<double, 3>(
		Vec<double, 3>({
			currentCords[0],
			currentCords[1],
			currentCords[2],
		}) / currentCords[3],
		v.GetProperties()
	);
}


} // namespace artisan_gfx
