#include "obj.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace artisan_gfx {

namespace obj_parser {

OBJParser::OBJParser() : max_v_value(0) {}

Triangle3 OBJParser::FaceToTriangle(F f) {
	return Triangle3(
		FaceComponentToVertex(f.A),
		FaceComponentToVertex(f.B),
		FaceComponentToVertex(f.C)
	);
}

std::vector<Triangle3> OBJParser::GetTriangles() {
	std::vector<Triangle3> triangles;
	for(unsigned int i = 0; i < parsed_f.size(); i++) {
		triangles.push_back(FaceToTriangle(parsed_f[i]));
	}
	return triangles;
}

Vertex3 OBJParser::FaceComponentToVertex(FComponent f_c) {
	V v = parsed_v[f_c[0]];
	v.xyz = v.xyz / max_v_value;

	VT vt = parsed_vt[f_c[1]];
	VN vn = parsed_vn[f_c[2]];
	Vertex3 vrtx(v.xyz);

	vrtx["vt_u"] = vt.uvw[0];
	vrtx["vt_v"] = vt.uvw[1];
	vrtx["vt_w"] = vt.uvw[2];

	vrtx["vn_x"] = vn.xyz[0];
	vrtx["vn_y"] = vn.xyz[1];
	vrtx["vn_z"] = vn.xyz[2];

	return vrtx;
}

void OBJParser::Parse(std::string file) {
	std::string line;
	std::ifstream obj_file(file);
	
	while (getline(obj_file, line)) {
		ParseLine(line);
	}
	
	obj_file.close();
}

void OBJParser::ParseLine(std::string line) {
	std::vector<std::string> line_components;
	boost::split(line_components, line, boost::is_any_of(" "), boost::token_compress_on);
	if(line_components.size() > 0) {
		if(line_components[0] == "v") {
			ParseV(line_components);
		}
		if(line_components[0] == "vt") {
			ParseVT(line_components);
		}
		if(line_components[0] == "vn") {
			ParseVN(line_components);
		}
		if(line_components[0] == "f") {
			ParseF(line_components);
		}
	}
	return;
}

void OBJParser::ParseV(std::vector<std::string> line_components) {
	V v;
	v.xyz = ParseVExpression(line_components);
	for(int i = 0; i < 3; i ++) {
		if(std::abs(v.xyz[i]) > max_v_value) {
			max_v_value = std::abs(v.xyz[i]);
		}
	}
	parsed_v.push_back(v);
}

void OBJParser::ParseVT(std::vector<std::string> line_components) {
	VT vt;
	vt.uvw = ParseVExpression(line_components);
	parsed_vt.push_back(vt);
}

void OBJParser::ParseVN(std::vector<std::string> line_components) {
	VN vn;
	vn.xyz = ParseVExpression(line_components);
	parsed_vn.push_back(vn);
}

void OBJParser::ParseF(std::vector<std::string> line_components) {
	F f;
	f.A = ParseFaceExpression(line_components[1]);
	f.B = ParseFaceExpression(line_components[2]);
	f.C = ParseFaceExpression(line_components[3]);
	parsed_f.push_back(f);
}

Vec3 ParseVExpression(std::vector<std::string> v_line) {
	Vec3 parts;
	parts[0] = std::stod(v_line[1]);
	parts[1] = std::stod(v_line[2]);
	parts[2] = std::stod(v_line[3]);
	return parts;
}


FComponent ParseFaceExpression(std::string face_subexpression) {
	std::vector<std::string> subexpression_components;
	boost::split(subexpression_components, face_subexpression, boost::is_any_of("/"));
	FComponent parsed_face;
	parsed_face[0] = std::stoi(subexpression_components[0]) - 1;
	parsed_face[1] = std::stoi(subexpression_components[1]) - 1;
	parsed_face[2] = std::stoi(subexpression_components[2]) - 1;
	return parsed_face;
}

OBJ ParseOBJFile(std::string filename) {
	OBJParser p;
	p.Parse(filename);
	return OBJ(p.GetTriangles());
}

} // namespace obj_parser

} // namespace artisan_gfx
