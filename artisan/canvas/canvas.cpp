#include "canvas.h"

namespace artisan_gfx {

bool Canvas::CordInBounds(const int x, const int y) {
	bool xInBounds = x >= 0 && x < GetLength();
	bool yInBounds = y >= 0 && y < GetHeight();
	return xInBounds && yInBounds;
}

void Canvas::Fill(Color c) {
	for(int i = 0; i < GetLength(); i++) {
		for(int j = 0; j < GetHeight(); j++) {
			PutPixel(i, j, c);
			zbuffer_.Set(i,j, - std::numeric_limits<double>::max());
		}
	}
}

void Canvas::PutPixel(const int x, const int y, const double z, const Color c) {
	bool shouldDraw = zbuffer_.PutIfGreater(x,y,z);	
	if (shouldDraw) {
		PutPixel(x,y,c);
	}
}

void Canvas::DrawLine(const int x0, const int y0, const double z0, const int x1, const int y1, const double z1, Color c) {
	int independant_var_start = x0;
	int independant_var_end = x1;
	int dependant_var_start = y0;
	int dependant_var_end = y1;
	double z_start = z0;
	double z_end = z1;

	bool x_is_independant_var = true;

	if(y1 == y0 && x1 == x0) {
		PutPixel(x1, y1, z1, c);
		return;
	}

	if(std::abs(y1 - y0) > std::abs(x1 - x0)) {
	  x_is_independant_var = false;
		independant_var_start = y0;	
		independant_var_end = y1;	
		dependant_var_start = x0;
		dependant_var_end = x1;
	}

	if(independant_var_start > independant_var_end) {
		std::swap(independant_var_start, independant_var_end);
		std::swap(dependant_var_start, dependant_var_end);
		std::swap(z_start, z_end);
	}

	float	derror = std::abs( 
		(dependant_var_end - dependant_var_start) /
		float((independant_var_end - independant_var_start)));
	float error = 0;
	bool slope_is_positive = dependant_var_end > dependant_var_start;
	int d = dependant_var_start;
	double z_slope = (z_end - z_start) / (independant_var_end - independant_var_start);


	if (independant_var_start < 0) {
		independant_var_start = 0;
	}

	if (x_is_independant_var) {
		if (independant_var_end > GetLength()) {
			independant_var_end = GetLength();
		}
	} else {
		if (independant_var_end > GetHeight()) {
			independant_var_end = GetHeight();
		}
	}
	
	for (int i = independant_var_start; i <= independant_var_end; i++) {
			if (x_is_independant_var) {
				PutPixel(i, d, z_start + (i - independant_var_start) * z_slope, c);
			} else {
				PutPixel(d, i, z_start + (i - independant_var_start) * z_slope, c);
			}
			error += derror;
			if (error >= 1) {
					if (slope_is_positive) {
						d += 1;
					} else {
						d -= 1;
					}
					error -= 1;
			}
	}

	
}

void Canvas::DrawLine(const int x0, const int y0, const int x1, const int y1, Color c) {
	DrawLine(x0, y0, std::numeric_limits<double>::max(), x1, y1, std::numeric_limits<double>::max(), c);
}

void Canvas::DrawLine(const cpoint A, const cpoint B, const Color c) {
	DrawLine(A[0], A[1], A.z, B[0], B[1], B.z, c);
}

void Canvas::ColorTriangle(CTriangle& t, Color& c) {
	BoundingBox bb = BoundingBoxOf(t);
	for (int i = bb.top_left[0]; i < bb.bottom_right[0]; i++) {
		for (int j = bb.top_left[1]; j < bb.bottom_right[1]; j++) {
			Vec<int, 2> bbox_loc({i, j});
			Vec3 bary = BarycentricCords(bbox_loc, t);	
			double z = bary * Vec3({t.GetA().z, t.GetB().z, t.GetC().z});
			if ( BarycentricIsInternal(bary) ) {
				PutPixel(i, j, z, c);

			}
		}
	}
	
}

void Canvas::ShadeTriangle(Shader& s, Triangle3& t) {
	Triangle3 vertex_shaded_triangle = s.Vertex(t);
	CTriangle ct = CTriangle(vertex_shaded_triangle);
	BoundingBox bb = BoundingBoxOf(ct);
	for (int i = bb.top_left[0]; i < bb.bottom_right[0]; i++) {
		for (int j = bb.top_left[1]; j < bb.bottom_right[1]; j++) {
			Vec<int, 2> bbox_loc({i, j});
			Vec3 bary = BarycentricCords(bbox_loc, ct);
			double z = bary * Vec3({ct.GetA().z, ct.GetB().z, ct.GetC().z});
			if ( BarycentricIsInternal(bary) ) {
				Color c = s.Fragment(bary, ct);
				PutPixel(i, j, z, c);
			}
		}
	}
}

} // namespace artisan_gfx
