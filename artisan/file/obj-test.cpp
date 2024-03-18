#include "gtest/gtest.h"
#include "obj.h"

namespace artisan_gfx {

TEST(OBJParserTest, Parses) {
	OBJ obj = obj_parser::ParseOBJFile("./artisan/assets/head.obj");
	EXPECT_EQ(obj.GetTriangles().size(), 2492);
}

} // namespace artisan_gfx
