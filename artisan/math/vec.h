#pragma once
#include <cmath>
#include <vector>
#include <array>
#include <initializer_list>
#include <stdexcept>

namespace artisan_gfx {

using std::sqrt;

template <class G, unsigned int D>
class Vec {
	std::array<G, D> elems;
public:
	Vec() = default;

	Vec(std::array<G,D> il) : elems(il) {}

	int Dimension() const {
		return D;
	}

	Vec<G,D> operator -() const {
		std::array<G,D> negelems;
    		for( unsigned int i = 0; i < D; i++ ) {
    			negelems [i] = elems[i] - elems[i] - elems[i];
    		}
    		return Vec(negelems);
	}

	G operator[] (int i) const {
		return elems[i];
	}

	G& operator[] (int i) {
		return elems[i];
	}

	G MagnitudeSquared() const {
		// Throws an exception for 0 dimensional vector.
		G sum = elems[0] * elems[0];
		for ( unsigned int i = 1; i < D; i++ ) {
			sum += elems[i] * elems[i];
		}
		return sum;
	} 

};

// Euclidian Magnitude
template <class G, unsigned int D>
double Magnitude(const Vec<G,D>& u) {
	return sqrt(u.MagnitudeSquared());
}

// Euclidian distance
template <class G, unsigned int D>
double DistanceBetween(const Vec<G,D>& u, const Vec<G,D>& v) {
	return Magnitude(u - v);
}

// Euclidian unit vector
template <class G, unsigned int D>
Vec<G,D> Normalize(const Vec<G,D>& u) {
	return u / Magnitude(u);
}

template <class G, unsigned int D>
bool operator==(const Vec<G,D>& u, const Vec<G,D>& v) {
	for(unsigned int i = 0; i < D; i++) {
		if ( u[i] != v[i] ) {
			return false;
		}
	}
	return true;
}

template<class G, unsigned int D>
Vec<G,D> operator+(const Vec<G,D>& u, const Vec<G,D>& v) {
	std::array<G,D> sum;
	for(unsigned int i = 0; i < D; i++) {
		sum[i] = u[i] + v[i];
	}
	return Vec<G,D>(sum);
}

template<class G, unsigned int D>
Vec<G,D> operator-(const Vec<G,D>& u, const Vec<G,D>& v) {
	std::array<G,D> diff;
	for(unsigned int i = 0; i < D; i++) {
		diff[i] = u[i] - v[i];
	}
	return Vec<G,D>(diff);
}

template<class G, unsigned int D>
G operator*(const Vec<G,D>& u, const Vec<G,D>& v) {
	G sum = u[0] * v[0];
	for(unsigned int i = 1; i < D; i++) {
		sum += u[i] * v[i];
	}
	return sum;
}

template<class G, class S, unsigned int D>
Vec<G,D> operator*(const Vec<G,D>& u, S s) {
	std::array<G,D> product;
	for(unsigned int i = 0; i < D; i++) {
		product[i] = s * u[i];
	}
	return Vec<G,D>(product);
}

template<class G, class S, unsigned int D>
Vec<G,D> operator*(S s, const Vec<G,D>& u) {
	std::array<G,D> product;
	for(unsigned int i = 0; i < D; i++) {
		product[i] = s * u[i];
	}
	return Vec<G,D>(product);
}

template<class G, unsigned int D>
Vec<G,D> operator/(const Vec<G,D>& u, G s) {
	std::array<G,D> quotient;
	for(unsigned int i = 0; i < D; i++) {
		quotient[i] = u[i] / s;
	}
	return Vec<G,D>(quotient);
}

} // namespace artisan_gfx
