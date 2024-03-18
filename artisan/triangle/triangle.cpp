#include "triangle.h"

namespace artisan_gfx {

Triangle4 ToHomogeneousTriangle(Triangle3 t) {
	return Triangle4(
		ToHomogeneousVertex(t.GetA()),
		ToHomogeneousVertex(t.GetB()),
		ToHomogeneousVertex(t.GetC()));
}

Triangle3 FromHomogeneousTriangle(Triangle4 t) {
	return Triangle3(
		FromHomogeneousVertex(t.GetA()),
		FromHomogeneousVertex(t.GetB()),
		FromHomogeneousVertex(t.GetC()));
}

} // namespace artisan_gfx
