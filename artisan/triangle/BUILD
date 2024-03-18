cc_library(
	name = "triangle",
	srcs = ["triangle.cpp"],
	hdrs = ["triangle.h"],
	visibility = ["//visibility:public"],
	deps = [
		":vertex",
		"//artisan/math:ray",
		"//artisan/math:vec3",
		"//artisan/math:vec4",
	]
)

cc_test (
	name= "triangle-test",
	srcs = ["triangle-test.cpp"],
	deps = [
		":triangle",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)
cc_library(
	name = "vertex",
	srcs = ["vertex.cpp"],
	hdrs = ["vertex.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:ray",
		"//artisan/math:vec3",
	]
)

cc_test (
	name= "vertex-test",
	srcs = ["vertex-test.cpp"],
	deps = [
		":vertex",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

