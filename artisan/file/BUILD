cc_library(
	name = "ppm",
	srcs = ["ppm.cpp"],
	hdrs = ["ppm.h"],
	visibility = ["//visibility:public"],
	deps = [
		":tga",	
	],
)

cc_test (
	name= "ppm-test",
	srcs = ["ppm-test.cpp"],
	deps = [
		":ppm",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_library(
	name = "obj",
	srcs = ["obj.cpp"],
	hdrs = ["obj.h"],
	deps = [
		"@boost//:algorithm",
		"//artisan/math:vec3",
		"//artisan/triangle:triangle",
	],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "obj-test",
	srcs = ["obj-test.cpp"],
	data = [
		"//artisan/assets:assets",
	],
	deps = [
		":obj",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	]
)

cc_library(
	name = "tga",
	srcs = ["tga.cpp"],
	hdrs = ["tga.h"],
	deps = [
		"//artisan/math:vec",
		"//artisan/math:vec3",
		"@com_google_absl//absl/status",
		"@com_google_absl//absl/status:statusor",
		"@com_google_absl//absl/strings:str_format",
	],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "tga-test",
	srcs = ["tga-test.cpp"],
	data = [
		"//artisan/assets:assets",
	],
	deps = [
		":tga",
		":ppm",
		"@gtest//:gtest",
		"@gtest//:gtest_main"
	],
)
