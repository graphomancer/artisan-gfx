cc_library(
	name = "shader",
	srcs = ["shader.cpp"],
	hdrs = ["shader.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/file:tga",
		"//artisan/triangle:triangle",
		"//artisan/math:mat",
		"//artisan/math:vec3",
		"//artisan/canvas:ctriangle",
	]
)

cc_library(
	name = "simple-tga-shader",
	srcs = ["simple-tga-shader.cpp"],
	hdrs = ["simple-tga-shader.h"],
	visibility = ["//visibility:public"],
	deps = [
		":shader",
		"//artisan/math:transform",
	]

)

cc_library(
	name = "phong-shader",
	srcs = ["phong-shader.cpp"],
	hdrs = ["phong-shader.h"],
	visibility = ["//visibility:public"],
	deps = [
		":shader",
		"//artisan/math:transform",
		"//artisan/math:vec2",
	]
)

cc_library(
	name = "directional-light-shader",
	srcs = ["directional-light-shader.cpp"],
	hdrs = ["directional-light-shader.h"],
	visibility = ["//visibility:public"],
	deps = [
		":shader",
		"//artisan/math:transform",
		"//artisan/math:vec2",
	]
)

cc_library(
	name = "color-and-light-shader",
	srcs = ["color-and-light-shader.cpp"],
	hdrs = ["color-and-light-shader.h"],
	visibility = ["//visibility:public"],
	deps = [
		":shader",
		"//artisan/math:transform",
		"//artisan/math:vec2",
	]
)
