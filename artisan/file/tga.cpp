#include "tga.h"
#include <iostream> 
#include <string>
#include <fstream>
#include <utility>
#include <string_view>
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"

namespace artisan_gfx {

Color RGBAToVec3(RGBAColor rgba) {
	return Color({
		(double) rgba.r,
		(double) rgba.g,
		(double) rgba.b
	});
}

namespace tga_parser {

int BitsToBytes(const uint8_t bit_count) {
	// round up to account for case of bits_per_pixel value of 15.
	return bit_count/8 + (bit_count % 8 != 0);
}

absl::StatusOr<RGBAColor> ParseTGAColor(const uint8_t * color_data, const uint8_t bits_per_pixel) {
	RGBAColor color;
	switch(bits_per_pixel ) {
		case 8:
			color.a = 255;
			color.g = color_data[0];
			color.b = color_data[0];
			color.r = color_data[0];
			return color;
		case 15:
			return absl::UnimplementedError("'bits_per_pixel' value unimplemented");
		case 16:
			return absl::UnimplementedError("'bits_per_pixel' value unimplemented");
		case 24:
			color.a = 255;
			color.r = color_data[2];
			color.g = color_data[1];
			color.b = color_data[0];
			return color;
		case 32:
			color.a = color_data[3];
			color.r = color_data[2];
			color.g = color_data[1];
			color.b = color_data[0];
			return color;

	}
	return absl::InvalidArgumentError(absl::StrFormat("Invalid 'bits_per_pixel' value for TGA" "file. bits_per_pixel must be one of '8', '15', '16', '24', '32' but was %d", bits_per_pixel));
}

std::pair<PacketHeaderType, int> ParsePacketHeader(uint8_t packet_header) {
	PacketHeaderType type = RAW;
	if(packet_header >= 128) {
		type = RUN_LENGTH;
		packet_header -= 128;
	}
	return std::make_pair(type, packet_header + 1);
}

absl::StatusOr<std::vector<RGBAColor>> ParseRunLengthPixels(std::ifstream &in, const int repitition_count, const uint8_t bits_per_pixel) {
	uint8_t read_chunk[4] = {0, 0, 0, 0};
	in.read(reinterpret_cast<char *>(read_chunk), BitsToBytes(bits_per_pixel));
	if(!in.good()) { 
		if (!in.fail()) {
			return absl::UnavailableError(absl::StrFormat("ParseRunLengthPixels: error reading input stream. good()=%d eof=%d fail=%d bad=%d", in.good(), in.eof(), in.fail(), in.bad()));
		}
	}
	absl::StatusOr<RGBAColor> maybe_color = ParseTGAColor(read_chunk, bits_per_pixel);
	if (!maybe_color.ok()) {
		return maybe_color.status();
	}
	std::vector<RGBAColor> parsed_colors;
	for(int i = 0; i < repitition_count; i++) {
		parsed_colors.push_back(maybe_color.value());
	}
	return parsed_colors;
}

absl::StatusOr<std::vector<RGBAColor>> ParseRawPixels(std::ifstream &in, const int raw_count, const uint8_t bits_per_pixel) {
	std::vector<RGBAColor> parsed_colors;
	for(int i = 0; i < raw_count; i++) {
		uint8_t raw_chunk[4] = {0, 0, 0, 0};
		in.read(reinterpret_cast<char *>(raw_chunk), BitsToBytes(bits_per_pixel));

		if(!in.good()) {
			if(!in.fail()) {
				return absl::UnavailableError(absl::StrFormat("ParseRunLengthPixels: error reading input stream. good()=%d eof=%d fail=%d bad=%d", in.good(), in.eof(), in.fail(), in.bad()));
			}
		}
		absl::StatusOr<RGBAColor> maybe_color = ParseTGAColor(raw_chunk, bits_per_pixel);
		if (!maybe_color.ok()) {
			return maybe_color.status();
		}
		parsed_colors.push_back(maybe_color.value());
	}

	return parsed_colors;
}

absl::StatusOr<std::vector<RGBAColor>> ReadRLEEncodedTGAData(std::ifstream &in, size_t num_pixels, const uint8_t bits_per_pixel) {
	size_t pixel_count = 0;
	std::vector<RGBAColor> read_pixels;
	while(pixel_count < num_pixels) {
		std::pair<PacketHeaderType, int> parsed_header = ParsePacketHeader(in.get());
		absl::StatusOr<std::vector<RGBAColor>> maybe_read_pixels_batch;
		if(parsed_header.first == RUN_LENGTH) {
			maybe_read_pixels_batch = ParseRunLengthPixels(in, parsed_header.second, bits_per_pixel);
		} else {
			maybe_read_pixels_batch = ParseRawPixels(in, parsed_header.second, bits_per_pixel);
		}
		if (!maybe_read_pixels_batch.ok()) {
			return maybe_read_pixels_batch.status();
		}
		std::vector<RGBAColor> read_pixels_batch = maybe_read_pixels_batch.value();
		for(auto pixel : read_pixels_batch) {
			pixel_count += 1;
			read_pixels.push_back(pixel);
		}
	}
	return read_pixels;
}

absl::StatusOr<TGAHeader> ReadTGAHeader(std::ifstream &in) {
	TGAHeader header;
	in.read(reinterpret_cast<char *>(&header), sizeof(header));
	if(!in.good()) {
		return absl::UnavailableError("ReadTGAHeader: error reading input stream");
	}
	return header;
}

void PrintTGAHeader(TGAHeader h) {
    std::cout << "id_length: " << int(h.id_length) << std::endl;
    std::cout << "color_map_type: " << int(h.color_map_type) << std::endl;
    std::cout << "data_type_code: " << int(h.data_type_code) << std::endl;
    std::cout << "color_map_origin: " << int(h.color_map_origin) << std::endl;
    std::cout << "color_map_length: " << int(h.color_map_length) << std::endl;
    std::cout << "color_map_depth: " << int(h.color_map_depth) << std::endl;
    std::cout << "x_origin: " << int(h.x_origin) << std::endl;
    std::cout << "y_origin: " << int(h.y_origin) << std::endl;
    std::cout << "width: " << int(h.width) << std::endl;
    std::cout << "height: " << int(h.height) << std::endl;
    std::cout << "bits_per_pixel: " << int(h.bits_per_pixel) << std::endl;
    std::cout << "image_descriptor: " << int(h.image_descriptor) << std::endl;
}

absl::StatusOr<TGA> ParseTGAFile(std::string file_path) {
	std::ifstream in(file_path);

	absl::StatusOr<TGAHeader> maybe_header = ReadTGAHeader(in);
	if(!maybe_header.ok()) {
		return maybe_header.status();
	}
	TGAHeader header = maybe_header.value();
	size_t num_pixels = header.width * header.height;
	auto data = ReadRLEEncodedTGAData(in, num_pixels, header.bits_per_pixel);
	if (!data.ok()) {
		return data.status();
	}
	return TGA(header, data.value());
}

} // namespace tga_parser

} // namespace artisan_gfx
