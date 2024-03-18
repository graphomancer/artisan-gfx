cc_library(
	name = "material-hittable-list",
	srcs = ["material-hittable-list.cpp"],
	hdrs = ["material-hittable-list.h"],
	visibility = ["//visibility:public"],
	deps = [
		":material-hittable",
	]
)

cc_test(
	name = "material-hittable-list-test",
	srcs = ["material-hittable-list-test.cpp"],
	visibility = ["//visibility:public"],
	deps = [
		":material-hittable-list",
		"//artisan/raytracer/geometry:sphere",
		"//artisan/math:vec3",
		"//artisan/raytracer/material:lambertian",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_library(
	name = "material-hittable",
	srcs = ["material-hittable.cpp"],
	hdrs = ["material-hittable.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/raytracer/geometry:hittable",
		"//artisan/raytracer/material:material",
	],
)
