#include <iostream>
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "artisan/math/vec.h"
#include "artisan/math/vec3.h"
#include <vector>
#include <utility>
#include <algorithm>

namespace artisan_gfx {

#pragma once

#pragma pack(push,1)
typedef struct {
    std::uint8_t  id_length = 0;
    std::uint8_t  color_map_type = 0;
    std::uint8_t  data_type_code = 0;
    std::uint16_t color_map_origin = 0;
    std::uint16_t color_map_length = 0;
    std::uint8_t  color_map_depth = 0;
    std::uint16_t x_origin = 0;
    std::uint16_t y_origin = 0;
    std::uint16_t width = 0;
    std::uint16_t height = 0;
    std::uint8_t  bits_per_pixel = 0;
    std::uint8_t  image_descriptor = 0;
} TGAHeader;
#pragma pack(pop)

void PrintTGAHeader(TGAHeader h);

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} RGBAColor;

Color RGBAToVec3(RGBAColor rgba);

enum PacketHeaderType {
	RUN_LENGTH,
	RAW,
};

class TGA {
	const TGAHeader & header;
	std::vector<std::vector<RGBAColor>> pixels;
public:
	TGA(TGAHeader h, std::vector<RGBAColor> pixel_data) : header(h) {
		std::vector<RGBAColor> row;
		int num_rows = int(pixel_data.size())/header.width;

		int pixel_count = 0;
		for(int i = 0; i < num_rows; i++) {
			std::vector<RGBAColor> row_segment;
			for(int j = 0; j < header.width; j++) {
				if(false && pixel_count >= pixel_data.size()) {
					row_segment.push_back(RGBAColor());
				} else {
					row_segment.push_back(pixel_data[pixel_count]);
				}
				pixel_count += 1;
			}
			pixels.push_back(row_segment);
		}
		if(!(header.image_descriptor & 0x20)) {
			FlipVertically();
		}
		if(header.image_descriptor & 0x10) {
			FlipHorizontally();
		}
	}
	std::vector<std::vector<RGBAColor>> GetPixels() { return pixels; }
	void FlipHorizontally() {
		for(auto row: pixels) {
			std::reverse(row.begin(), row.end());
		}
	}
	void FlipVertically() {
		std::reverse(pixels.begin(), pixels.end());
	}

	int width() const {
		if (pixels.size() > 0) {
			return pixels[0].size();
		}
		return -1;
	}
	int height() const {
		return pixels.size();
	}
	RGBAColor get(int r, int c) const {
		return pixels[r][c];
	}
	RGBAColor getUV(double u, double v) const {
		return get((1 - v) * height(), u * width());
	}
	RGBAColor getUV(Vec<double, 2> uv) const {
		return getUV(uv[0], uv[1]);
	}
};

class TGANormalmap {
public: 
	const TGA tga;
	TGANormalmap(TGA t) : tga(t) {}
	Vec3 getUV(double u, double v) const {
		RGBAColor c = tga.getUV(u, v);
		return Vec3({
				double(c.r - 1),
			       	double(c.g - 1),
			       	double(c.b - 1)
			}) * 2/255. - Vec3({1, 1, 1});
	}
	Vec3 getUV(Vec<double, 2> uv) const {
		return getUV(uv[0], uv[1]);
	}
};

class TGASpecularmap {
public:
	const TGA tga;
	TGASpecularmap(TGA t) : tga(t) {}
	double getUV(double u, double v) const {
		RGBAColor c = tga.getUV(u, v);
		return c.b;
	}
	double getUV(Vec<double, 2> uv) const {
		return getUV(uv[0], uv[1]);
	}

};

namespace tga_parser { 
	int BitsToBytes(const uint8_t bit_count);
	absl::StatusOr<RGBAColor> ParseTGAColor(const uint8_t * color_data, const uint8_t bits_per_pixel);
	std::pair<PacketHeaderType, int> ParsePacketHeader(uint8_t packet_header);
	absl::StatusOr<TGAHeader> ReadTGAHeader(std::ifstream &in);
	absl::StatusOr<std::vector<RGBAColor>> ReadRLEEncodedTGAData(std::ifstream &in, const size_t num_pixels, const uint8_t bits_per_pixel);
	absl::StatusOr<std::vector<RGBAColor>> ParseRunLengthPixels(std::ifstream &in, const int repitition_count, const uint8_t bits_per_pixel);
	absl::StatusOr<std::vector<RGBAColor>> ParseRawPixels(std::ifstream &in, const int raw_count, const uint8_t bits_per_pixel);
	absl::StatusOr<TGA> ParseTGAFile(std::string tga_file);
} // namespace tga_parser 

} // namespace artisan_gfx
