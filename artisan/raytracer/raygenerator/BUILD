cc_library(
	name = "ray-generator",
	srcs = ["ray-generator.cpp"],
	hdrs = ["ray-generator.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:ray",
		"//artisan/math:trig",
		"//artisan/math:vec3",
	]
)

cc_test(
	name = "ray-generator-test",
	srcs = ["ray-generator-test.cpp"],
	deps = [
		":ray-generator",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)
