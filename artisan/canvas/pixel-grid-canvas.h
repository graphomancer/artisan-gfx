#pragma once
#include "canvas.h"
#include "artisan/file/ppm.h"

namespace artisan_gfx {

class PixelGridCanvas : public Canvas {
	PixelGrid pg;	

public:
	PixelGridCanvas(const int length_pixels, const int height_pixels);

	virtual int GetLength() const override;
	virtual int GetHeight() const override;
	virtual Color GetPixel(const int x, const int y) override;

	virtual void PutPixel(const int x, const int y, const Color c) override;

	PixelGrid GetPixelGrid();
};

} // namespace artisan_gfx
