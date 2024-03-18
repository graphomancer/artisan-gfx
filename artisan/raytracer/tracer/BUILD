cc_library(
	name = "tracer",
	srcs = ["tracer.cpp"],
	hdrs = ["tracer.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/raytracer/raygenerator:ray-generator",
		"//artisan/file:ppm",
		"//artisan/raytracer/geometry:hittable-list",
		"//artisan/math:stats",
		"//artisan/raytracer/materialhittable:material-hittable-list"
	]
)
