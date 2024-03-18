cc_library(
	name = "metal",
	srcs = ["metal.cpp"],
	hdrs = ["metal.h", "material.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:ray",
		"//artisan/math:vec3",
		"//artisan/raytracer/geometry:hittable",
	],
)
cc_library(
	name = "lambertian",
	srcs = ["lambertian.cpp"],
	hdrs = ["lambertian.h", "material.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:ray",
		"//artisan/math:vec3",
		"//artisan/raytracer/geometry:hittable",
	],
)

cc_library(
	name = "material",
	hdrs = ["material.h"],
	visibility = ["//visibility:public"],
)
