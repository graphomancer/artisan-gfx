#pragma once
#include "artisan/math/vec3.h"
#include "artisan/triangle/triangle.h"
#include <string>
#include <optional>
#include <boost/algorithm/string.hpp>

namespace artisan_gfx {

class OBJ {
	std::vector<Triangle3> triangles;
public:
	OBJ(std::vector<Triangle3> t) : triangles(t) {}
	std::vector<Triangle3> GetTriangles() { return triangles; }
};

namespace obj_parser {

// V represents a geometric Vertex having x, y, z coordinates
typedef struct {
	Vec3 xyz;
} V;

// VT represents texture coordinates, having a specified uv (and optionally w) mapping
typedef struct {
	Vec3 uvw;
} VT;

// VN represents a Vertex normal having specified x, y, z components
typedef struct {
	Vec3 xyz;
} VN;

typedef Vec<int, 3> FComponent;

// F represents a triangle. Each member of F represents a (vetex
// index/texture index/normal index) triplet, with each index 'i' representing
// the 'ith' entry of the specified type in the OBJ file, with indexing
// starting at 1 rather than 0.
typedef struct {
	FComponent A;
	FComponent B;
	FComponent C;
} F;

class OBJParser {
	std::vector<V> parsed_v;
	std::vector<VT> parsed_vt;
	std::vector<VN> parsed_vn;
	std::vector<F> parsed_f;
	double max_v_value;
	void ParseLine(std::string line);
	void ParseV(std::vector<std::string> line_components);
	void ParseVT(std::vector<std::string> line_components);
	void ParseVN(std::vector<std::string> line_components);
	void ParseF(std::vector<std::string> line_components);
	Vertex3 FaceComponentToVertex(FComponent f_c);
	Triangle3 FaceToTriangle(F f);
			
public:
	OBJParser();
	void Parse(std::string filename);
	std::vector<Triangle3> GetTriangles();
};

FComponent ParseFaceExpression(std::string face_subexpression);
Vec3 ParseVExpression(std::vector<std::string> v_expression);

OBJ ParseOBJFile(std::string filename);

} // namespace obj_parser

} // namespace artisan_gfx
