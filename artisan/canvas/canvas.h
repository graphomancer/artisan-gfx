#pragma once
#include "artisan/math/vec3.h"
#include "artisan/triangle/shader/shader.h"
#include "cpoint.h"
#include "ctriangle.h"
#include "zbuffer.h"
#include <cmath>
#include <limits>
#include <iostream>

namespace artisan_gfx {

class Canvas {
	public:
		ZBuffer zbuffer_;
		virtual int GetLength() const = 0;
		virtual int GetHeight() const = 0;
		virtual Color GetPixel(const int x, const int y) = 0;
		virtual void PutPixel(const int x, const int y, const Color c) = 0;
		virtual void PutPixel(const int x, const int y, const double z, const Color c);
		bool CordInBounds(const int x, const int y);
		void Fill(Color c);
		void DrawLine(const int x0, const int y0, const double z0, const int x1, const int y1, const double z1, Color c);
		void DrawLine(const int x0, const int y0, const int x1, const int y1, Color c);
		void DrawLine(const cpoint A, const cpoint B, const Color c);
		void ColorTriangle(CTriangle& t, Color& c);
		void ShadeTriangle(Shader& s, Triangle3& t);
};

} // namespace artisan_gfx
