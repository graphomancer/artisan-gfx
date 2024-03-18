cc_library(
	name = "trig",
	hdrs = ["trig.h"],
	deps = [],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "vec4",
	srcs = ["vec4.cpp"],
	hdrs = ["vec4.h"],
	deps = [":vec3", ":vec"],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "vec3",
	srcs = ["vec3.cpp"],
	hdrs = ["vec3.h"],
	deps = [":stats", ":vec"],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "vec2",
	srcs = [],
	hdrs = ["vec2.h"],
	deps = [":vec"],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "vec",
	srcs = [],
	hdrs = ["vec.h"],
	deps = [],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "mat",
	srcs = ["mat.cpp"],
	hdrs = ["mat.h"],
	deps = [
		"//artisan/triangle:vertex",
		"//artisan/triangle:triangle",
		":vec"
	],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "transform",
	srcs = ["transform.cpp"],
	hdrs = ["transform.h"],
	deps = [
		":mat",
		":vec",
	],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "stats",
	srcs = ["stats.cpp"],
	hdrs = ["stats.h"],
	visibility = ["//visibility:public"],
)

cc_library(
	name = "ray",
	srcs = ["ray.cpp"],
	hdrs = ["ray.h"],
	deps = [":vec3"],
	visibility = ["//visibility:public"],
)

cc_test (
	name = "transform-test",
	srcs = ["transform-test.cpp"],
	deps = [
		":transform",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	],
)

cc_test (
	name = "vec-test",
	srcs = ["vec-test.cpp"],
	deps = [
		":vec",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_test (
	name = "mat-test",
	srcs = ["mat-test.cpp"],
	deps = [
		":mat",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)
cc_test (
	name= "vec3-test",
	srcs = ["vec3-test.cpp"],
	deps = [
		":vec3",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)
cc_test (
	name= "vec4-test",
	srcs = ["vec4-test.cpp"],
	deps = [
		":vec4",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)


cc_test (
	name= "ray-test",
	srcs = ["ray-test.cpp"],
	deps = [
		":ray",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)
