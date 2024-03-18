#pragma once
#include "artisan/triangle/vertex.h"

namespace artisan_gfx {

class CVertex : public Vertex<int, 2> {
public:
	double z;
	CVertex(Vertex3& v) : Vertex<int, 2>({int(v[0]), int(v[1])}, v.GetProperties()), z(v[2])  {};
};

} // namespace artisan_gfx
