#include "gtest/gtest.h"
#include "zbuffer.h"

namespace artisan_gfx {

const double lowest_double = std::numeric_limits<double>::lowest();

TEST(ZbufferTest, UpdateIfGreater) {
	ZBuffer buf(10, 10);
	EXPECT_EQ(buf.Get(5,5), lowest_double);
	buf.PutIfGreater(5,5,0);
	EXPECT_EQ(buf.Get(5,5), 0);
	buf.PutIfGreater(5,5,-1);
	EXPECT_EQ(buf.Get(5,5), 0);
	buf.PutIfGreater(5,5,10);
	EXPECT_EQ(buf.Get(5,5), 10);
}

} // namespace artisan_gfx
