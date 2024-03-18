#include "ppm.h"
#include "tga.h"
#include <sstream>
#include <iostream>

namespace artisan_gfx {

using namespace std;

PPM::PPM(PixelGrid pg, int mcv) {
	// validate pixels
	for(int i = 0; i < int(pg.size()); i++) {
		PixelRow pr = pg.at(i);
		if (pr.size() != pg.at(0).size()) {
			std::ostringstream errstr;
			errstr << "PixelGrid passed to PPM must be rectangular, but supplied PixelGrid was not. ";
			errstr << "Number of pixels on row " << i << "does not match number of pixels on previous rows. ";
			throw errstr.str();
		}
		for (int j = 0; j < int(pr.size()); j++) {
			Pixel p = pr.at(j);
			if (p.R < 0 || p.G < 0 || p.B < 0 ||
				p.R > mcv || p.G > mcv || p.B > mcv) {
				std::ostringstream errstr;
				errstr << "Pixel R/G/B values out of range. ";
				errstr << "Min allowed value : 0. Max allowed Value : " << mcv << ".  ";
				errstr << "Got : " << p.R << " / " << p.G << " / " << p.B << ". ";
				errstr << "Pixel located at (row, column): " << "(" << i << ", " << j << "). ";
				throw errstr.str();
			}
		}
	}
	pixel_grid = pg;
	max_color_value = mcv;
}

PPM::PPM(TGA tga) {
	for(auto& row : tga.GetPixels()) {
		PixelRow ppm_row;
		for(auto& tga_color : row) { 
			Pixel ppm_pixel;
			ppm_pixel.R = tga_color.r;
			ppm_pixel.G = tga_color.g;
			ppm_pixel.B = tga_color.b;
			ppm_row.push_back(ppm_pixel);
		}
		pixel_grid.push_back(ppm_row);
	}
	max_color_value = 255;
}

int PPM::GetMaxColorValue() { return max_color_value; }

int PPM::GetRowCount() { return pixel_grid.size(); }

int PPM::GetColCount() {
	if (pixel_grid.size() == 0) {
		return 0;
	}
	return pixel_grid.at(0).size();
}

PPM PPM::FlipHorizontal() {
	std::vector<PixelRow> newGrid;
	for(int i = GetRowCount() - 1; i >=0; i--) {
		newGrid.push_back(pixel_grid.at(i));
	}
	return PPM(newGrid, max_color_value);
}


string PPM::FileContents() {
	std::ostringstream buffer;
	buffer << "P3\n"; // Magic number indicating filetype
	buffer << this->GetColCount() << " " << this->GetRowCount() << "\n";
	buffer << this->GetMaxColorValue() << "\n";
	for (PixelRow pr : pixel_grid) {
		for (Pixel p : pr) {
			buffer << p.R << " " << p.G << " " << p.B << "\n";
		}
	}
	return buffer.str();
}

} // namespace artisan_gfx
