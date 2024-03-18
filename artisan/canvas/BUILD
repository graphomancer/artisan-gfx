cc_library(
	name = "pgcanvas",
	srcs = ["pixel-grid-canvas.cpp"],
	hdrs = ["pixel-grid-canvas.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/file:ppm",
		"//artisan/math:vec3",
		":canvas",
		":cpoint",
		":ctriangle",
		":zbuffer",
	]
)

cc_library(
	name = "canvas",
	hdrs = ["canvas.h"],
	srcs = ["canvas.cpp"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:vec3",
		"//artisan/triangle/shader:shader",
		":cpoint",
		":ctriangle",
		":zbuffer",
	]
)



cc_test (
	name = "pgcanvas-test",
	srcs = ["pixel-grid-canvas-test.cpp"],
	deps = [
		":pgcanvas",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_library(
	name = "zbuffer",
	srcs = ["zbuffer.cpp"],
	hdrs = ["zbuffer.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/file:ppm",
	],
)

cc_test (
	name = "zbuffer-test",
	srcs = ["zbuffer-test.cpp"],
	deps = [
		":zbuffer",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_library(
	name = "cpoint",
	srcs = ["cpoint.cpp"],
	hdrs = ["cpoint.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/math:vec",
		":ctriangle",
	]
)

cc_test(
	name = "cpoint-test",
	srcs = ["cpoint-test.cpp"],
	deps = [
		":cpoint",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_library(
	name = "ctriangle",
	srcs = ["ctriangle.cpp"],
	hdrs = ["ctriangle.h"],
	visibility = ["//visibility:public"],
	deps = [
		":cvertex",
		"//artisan/triangle:triangle",
	]
)

cc_test(
	name = "ctriangle-test",
	srcs = ["ctriangle-test.cpp"],
	deps = [
		":ctriangle",
		":cvertex",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)


cc_library(
	name = "cvertex",
	srcs = [],
	hdrs = ["cvertex.h"],
	visibility = ["//visibility:public"],
	deps = [
		"//artisan/triangle:vertex",
	]
)

cc_test (
	name= "cvertex-test",
	srcs = ["cvertex-test.cpp"],
	deps = [
		":cvertex",
		"//artisan/triangle:vertex",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

