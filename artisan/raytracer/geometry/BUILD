cc_library(
	name = "hittable",
	hdrs = ["hittable.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:ray",
		"//artisan/math:vec3",
	],
)

cc_library(
	name = "hittable-list",
	srcs = ["hittable-list.cpp"],
	hdrs = ["hittable-list.h", "hittable.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:ray",
		"//artisan/math:vec3",
	]
)

cc_test (
	name = "hittable-list-test",
	srcs = ["hittable-list-test.cpp"],
	deps = [
		":hittable-list",
		":sphere",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_library(
	name = "sphere",
	srcs = ["sphere.cpp"],
	hdrs = ["sphere.h", "hittable.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:ray",
		"//artisan/math:vec3",
	]
)

cc_test (
	name= "sphere-test",
	srcs = ["sphere-test.cpp"],
	deps = [
		":sphere",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)
