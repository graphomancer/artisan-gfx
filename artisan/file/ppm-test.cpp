#include "gtest/gtest.h"
#include "ppm.h"

namespace artisan_gfx {

const int happy_max_color_value = 6;
PixelGrid happy_pg{
	PixelRow{
		Pixel{ 1,1,1 }, Pixel{ 2,2,2}, Pixel{3,3,3}
    },
	PixelRow{
    	Pixel{ 4,4,4 }, Pixel{ 5,5,5}, Pixel{6,6,6}
    }
};

PixelGrid nonrectangular_pg{
	PixelRow{
		Pixel{ 1,1,1 }, Pixel{ 2,2,2}, Pixel{3,3,3}
    },
	PixelRow{
    	Pixel{ 4,4,4 }, Pixel{ 5,5,5}
    }
};

TEST(PPMUtilTest, BuildHappyPath) {
	PPM ppm = PPM(happy_pg, happy_max_color_value);
	EXPECT_EQ(ppm.GetColCount(), 3);
	EXPECT_EQ(ppm.GetRowCount(), 2);
	EXPECT_EQ(ppm.GetMaxColorValue(), happy_max_color_value);
}

TEST(PPMUtilTest, BuildOutOfRangeCausesError) {
	EXPECT_THROW(PPM(happy_pg, happy_max_color_value - 1), std::string);
}

TEST(PPMUtilTest, BuildNonRectangularCausesError) {
	EXPECT_THROW(PPM(nonrectangular_pg, happy_max_color_value), std::string);
}

} // namespace artisan_gfx
