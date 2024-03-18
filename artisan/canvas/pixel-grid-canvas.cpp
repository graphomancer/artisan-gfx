#include "pixel-grid-canvas.h"

namespace artisan_gfx {

PixelGridCanvas::PixelGridCanvas(const int length_pixels, const int height_pixels) {
	for(int i = 0; i < height_pixels; i++) {
		PixelRow pr;
		for(int j = 0; j < length_pixels; j++) {
			pr.push_back(Pixel{0,0,0});
		}
		pg.push_back(pr);
	}
	zbuffer_ = ZBuffer(length_pixels,height_pixels);
}

int PixelGridCanvas::GetLength() const {
	if(GetHeight() == 0) {
		return 0;
	}
	return pg[0].size();
}

int PixelGridCanvas::GetHeight() const {
	return pg.size();
}

void PixelGridCanvas::PutPixel(const int x, const int y, const Color c) {
	if(CordInBounds(x, y)) {
		pg[y][x] = Pixel{(int) c[0],(int) c[1],(int) c[2]};
	}
}

Color PixelGridCanvas::GetPixel(const int x, const int y) {
	if(CordInBounds(x,y)) {
		Pixel p = pg[y][x];
		return Vec3({p.R, p.G, p.B});
	}
	return Color({0,0,0});
}

PixelGrid PixelGridCanvas::GetPixelGrid() {
	return pg;
}

} // namespace artisan_gfx
