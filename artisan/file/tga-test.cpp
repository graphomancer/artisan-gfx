#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include "tga.h"
#include "absl/status/status.h"
#include "ppm.h"

namespace artisan_gfx {

TEST(TGATest, ReadTGA) {
	absl::StatusOr<TGA> maybe_parsed_image = tga_parser::ParseTGAFile("./artisan/assets/head.tga");
	EXPECT_EQ(maybe_parsed_image.status(), absl::OkStatus());
	TGA tga = maybe_parsed_image.value();
	EXPECT_EQ(tga.width(), 1024);
	EXPECT_EQ(tga.height(), 1024);
}

} // namespace artisan_gfx
