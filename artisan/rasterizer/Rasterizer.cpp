#include <iostream>
#include <algorithm>
#include "artisan/canvas/pixel-grid-canvas.h"
#include "artisan/file/obj.h"
#include "artisan/file/ppm.h"
#include "artisan/triangle/triangle.h"
#include "artisan/triangle/vertex.h"
#include "artisan/math/vec3.h"
#include "artisan/math/mat.h"
#include "artisan/math/transform.h"
#include "artisan/math/stats.h"
#include "artisan/canvas/cpoint.h"
#include "artisan/canvas/ctriangle.h"
#include "artisan/triangle/shader/simple-tga-shader.h"
#include "artisan/triangle/shader/phong-shader.h"
#include "artisan/triangle/shader/directional-light-shader.h"
#include "artisan/triangle/shader/color-and-light-shader.h"
#include "artisan/file/tga.h"
#include <vector>
#include <utility>

using namespace artisan_gfx;

using namespace std;

int height = 800;
int width = 800;

Vec3 camera_eye = Vec3({0,0,3});
Vec3 camera_center = Vec3({0,0,0});
Vec3 camera_up = Vec3({0,1,0});
double r = -1./(Magnitude(camera_eye - camera_center));

Mat4 projection = Mat<double, 4, 4>({{
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0, r, 1}
		}});

Mat4 camera = CameraTransform(
			camera_eye,
			camera_center,
			camera_up
		);

Mat4 viewport = ViewportTransform(0, 0, width, height);

int main() {
	vector<Triangle3> triangles = obj_parser::ParseOBJFile("./artisan/assets/diablo3_pose.obj").GetTriangles();
	TGA diffuse_tga = tga_parser::ParseTGAFile("./artisan/assets/diablo3_pose.tga").value();
	TGANormalmap normalmap_tga = TGANormalmap(tga_parser::ParseTGAFile("./artisan/assets/diablo3_pose_nm.tga").value());
	TGASpecularmap specmap_tga = TGASpecularmap(tga_parser::ParseTGAFile("./artisan/assets/diablo3_pose_spec.tga").value());

	vector<Triangle3> teapot = obj_parser::ParseOBJFile("./artisan/assets/teapot.obj").GetTriangles();

	PhongShader ps(viewport, projection, camera, Vec3({1,1,1}), diffuse_tga,
			normalmap_tga, specmap_tga);
	SimpleTGAShader s(viewport * projection * camera, diffuse_tga);

	DirectionalLightShader ds(viewport, projection, camera, Vec3({1,1,1}), diffuse_tga,
			normalmap_tga);

	ColorAndLightShader cs(viewport, projection, camera, Vec3({1,1,1}), Color({255, 255, 255}));
	
	PixelGridCanvas pgcanvas = PixelGridCanvas(width, height);


	for(unsigned int i = 0; i < teapot.size(); i++) {
		pgcanvas.ShadeTriangle(cs, teapot[i]);
	}

	PPM output(pgcanvas.GetPixelGrid(), 255);
	std::cout << output.FlipHorizontal().FileContents();
}
