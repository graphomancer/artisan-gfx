#pragma once
#include <unordered_map>
#include "artisan/math/vec.h"

namespace artisan_gfx {

typedef std::unordered_map<std::string, double> Properties;

template<class G, unsigned int D>
class Vertex {
	Vec<G,D> cords;
	Properties properties;
public:
	Vertex()  : cords(Vec<G,D>()), properties(Properties()) {}

	Vertex(Vec<G,D> cords) : cords(cords), properties(Properties()) {}

	Vertex(std::array<G,D> li) : cords(Vec<G,D>(li)), properties(Properties()) {}
	Vertex(std::array<G,D> li, Properties properties) : cords(Vec<G,D>(li)), properties(properties) {}
	
	Vertex(Vec<G,D> cords, Properties properties) : cords(cords), properties(properties) {}

	G operator[] (int i) const {
		return cords[i];
	}

	G& operator[] (int i) {
		return cords[i];
	}

	Vec<G,D> GetCords() const { return cords; }

	Properties GetProperties() const { return properties; }

	double& operator[](std::string key) {
		return properties[key];
	}

};

template<class G, unsigned int D>
bool operator==(const Vertex<G,D>& lhs, const Vertex<G,D>& rhs) {
	return lhs.GetCords() == rhs.GetCords() &&
		lhs.GetProperties() == rhs.GetProperties();
}

template<class G, unsigned int D>
bool operator!=(const Vertex<G,D>& lhs, const Vertex<G,D>& rhs) {
	return !(lhs == rhs);
}



typedef Vertex<double, 3> Vertex3;
typedef Vertex<double, 4> Vertex4;

Vertex4 ToHomogeneousVertex(Vertex3 v);

Vertex3 FromHomogeneousVertex(Vertex4 v);

} // namespace artisan_gfx
