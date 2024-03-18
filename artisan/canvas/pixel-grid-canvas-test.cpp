#include "gtest/gtest.h"
#include "pixel-grid-canvas.h"

namespace artisan_gfx {
	
TEST(PixelGridCanvasTest, PutsPixel_InBounds) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.PutPixel(1,1, Color({1,2,3}));
	for(int i = 0; i < pgLength; i++) {
		for(int j = 0; j < pgHeight; j++) {
			if(i == 1 && j == 1) {
				EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
			}
			else {
				EXPECT_EQ(pg.GetPixel(i,j), Color({0,0,0}));
			}
		}
	}
}


TEST(PixelGridCanvasTest, DrawLine_Slope_One) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.DrawLine(0,0,2,2, Color({1,2,3}));

	for(int i = 0; i < pgLength; i++) {
  		for(int j = 0; j < pgHeight; j++) {
  			if(i == j) {
  				EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
  			}
  			else {
  				EXPECT_EQ(pg.GetPixel(i,j), Color({0,0,0}));
  			}
  		}
	}
}


TEST(PixelGridCanvasTest, DrawLine_Horizontal) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.DrawLine(0,0,2,0, Color({1,2,3}));

	for(int i = 0; i < pgLength; i++) {
  	for(int j = 0; j < pgHeight; j++) {
  		if(j == 0) {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
  		}
  		else {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({0,0,0}));
  		}
  	}
	}
}


TEST(PixelGridCanvasTest, DrawLine_Vertical) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.DrawLine(0,0,0,2, Color({1,2,3}));

	for(int i = 0; i < pgLength; i++) {
  	for(int j = 0; j < pgHeight; j++) {
  		if(i == 0) {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
  		}
  		else {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({0,0,0}));
  		}
  	}
	}
}

TEST(PixelGridCanvasTest, DrawLine_Reverse_Cords) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.DrawLine(2,2,0,0, Color({1,2,3}));
	
	for(int i = 0; i < pgLength; i++) {
  	for(int j = 0; j < pgHeight; j++) {
  		if(i == j) {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
  		}
  		else {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({0,0,0}));
  		}
  	}
	}
}

TEST(PixelGridCanvasTest, DrawLine_Reverse_Cords_Y_Dependant) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.DrawLine(0,2,0,0, Color({1,2,3}));

	for(int i = 0; i < pgLength; i++) {
  	for(int j = 0; j < pgHeight; j++) {
  		if(i == 0) {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
  		}
  		else {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({0,0,0}));
  		}
  	}
	}
}

TEST(PixelGridCanvasTest, Fill) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.Fill(Color({1,2,3}));

	for(int i = 0; i < pgLength; i++) {
  		for(int j = 0; j < pgHeight; j++) {
  			EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
  		}
	}
}

TEST(PixelGridCanvasTest, Zvalues) {
	int pgLength = 3;
	int pgHeight = 3;
	PixelGridCanvas pg = PixelGridCanvas(pgLength,pgHeight);
	pg.Fill(Color({0,0,0}));
	pg.DrawLine(1,0, 1,  1,2, 1, Color({1,2,3}));
	pg.DrawLine(0,1, 0,  2,1, 0, Color({1,1,1}));    

	for(int i = 0; i <pgLength; i++) {
		for(int j = 0; j < pgHeight; j++) {
			if(i == 1) {
				EXPECT_EQ(pg.GetPixel(i,j), Color({1,2,3}));
			}
			else if(j == 1) {
				EXPECT_EQ(pg.GetPixel(i,j), Color({1,1,1}));
			}
			else {
				EXPECT_EQ(pg.GetPixel(i,j), Color({0,0,0}));
			}
		}
	}
}

} // namespace artisan_gfx
