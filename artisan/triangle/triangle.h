#pragma once

#include "artisan/math/vec3.h"
#include "artisan/math/vec4.h"
#include "vertex.h"
#include <vector>
#include <utility>

namespace artisan_gfx {

template<class VertexSubtype>
class Triangle {
	VertexSubtype A;
	VertexSubtype B;
	VertexSubtype C;
public:
	Triangle(const VertexSubtype A, const VertexSubtype B, const VertexSubtype C) : A(A), B(B), C(C) {}

	VertexSubtype& GetA() { return A; }
	VertexSubtype& GetB() { return B; }
	VertexSubtype& GetC() { return C; }

	std::vector<std::pair<VertexSubtype, VertexSubtype>> GetVertexPairs() {
		std::vector<std::pair<VertexSubtype,VertexSubtype>> VertexPairs;
		VertexPairs.push_back(std::make_pair(A, B));
		VertexPairs.push_back(std::make_pair(A, C));
		VertexPairs.push_back(std::make_pair(B, C));
		return VertexPairs;
	}

	std::vector<VertexSubtype> GetVerticiesByY() {
		VertexSubtype largest_y = A;
		VertexSubtype middle_y = B;
		VertexSubtype smallest_y = C;
	
		if(smallest_y[1] > middle_y[1]) {
			std::swap(smallest_y, middle_y);
		}
		if(middle_y[1] > largest_y[1]) {
			std::swap(middle_y, largest_y);
		}
		if(smallest_y[1] > middle_y[1]) {
			std::swap(smallest_y, middle_y);
		}
		std::vector<VertexSubtype> verticiesBy_y;
		verticiesBy_y.push_back(largest_y);
		verticiesBy_y.push_back(middle_y);
		verticiesBy_y.push_back(smallest_y);
		return verticiesBy_y;
	}
};

typedef Triangle<Vertex<double, 3>> Triangle3;
typedef Triangle<Vertex<double, 4>> Triangle4;

Triangle4 ToHomogeneousTriangle(Triangle3 t);
Triangle3 FromHomogeneousTriangle(Triangle4 t);

} // namespace artisan_gfx
