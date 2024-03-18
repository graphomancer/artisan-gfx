#pragma once
#include <vector>
#include <string>
#include "tga.h"

namespace artisan_gfx {
struct Pixel {
	int R;
	int G;
	int B;
};

typedef std::vector<Pixel> PixelRow;
typedef std::vector<PixelRow> PixelGrid;

class PPM {
	int max_color_value;
	PixelGrid pixel_grid;
public:
	PPM(PixelGrid, int max_color_value);
	PPM(TGA tga);
	int GetMaxColorValue();
	int GetRowCount();
	int GetColCount();
	PPM FlipHorizontal();
	std::string FileContents();
};

} // namespace artisan_gfx
