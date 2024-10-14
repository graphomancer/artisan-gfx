OPENGL_LINKOPTS = [
	"-lGL",
	"-lGLU",
	"-lX11",
	"-lXxf86vm",
	"-lXinerama",
	"-lXcursor",
	"-lpthread",
	"-lXrandr",
	"-lXi",
	"-ldl",
]

cc_binary(
	name = "example",
	srcs = ["example.cpp"],
	linkopts = OPENGL_LINKOPTS,
	deps = [
		"//third_party/glad",
		"@glfw//:glfw",
	],
)
