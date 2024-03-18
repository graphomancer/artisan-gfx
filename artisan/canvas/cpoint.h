#pragma once
#include "artisan/math/vec.h"

namespace artisan_gfx {

class cpoint  {
public:
	Vec<int, 2> cords;
	double z;

	cpoint() = default;

	cpoint(std::array<int,2> ic, double iz) : cords(ic), z(iz) {}

	cpoint(Vec<int,2> ic, double iz) : cords(ic), z(iz) {}

	cpoint operator -() const {
		return cpoint(-cords, -z);
	}

	int operator[] (int i) const {
		return cords[i];
	}

	int& operator[] (int i) {
		return cords[i];
	}

};

bool operator==(const cpoint u, const cpoint v);

cpoint operator+(const cpoint u, const cpoint v);

cpoint operator-(const cpoint u, const cpoint v);

template<class S>
cpoint operator*(S s, cpoint u) {
	return cpoint(s * u.cords, s * u.z);
}

template<class S>
cpoint operator*(cpoint u, S s) {
	return cpoint(s * u.cords, s * u.z);
}


} // namespace artisan_gfx
