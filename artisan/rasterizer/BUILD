cc_binary(
	name = "rasterizer",
	srcs = ["Rasterizer.cpp"],
	deps = [
		"//artisan/file:ppm",
		"//artisan/file:obj",
		"//artisan/triangle:triangle",
		"//artisan/triangle:vertex",
		"//artisan/canvas:pgcanvas",
		"//artisan/canvas:cpoint",
		"//artisan/canvas:ctriangle",
		"//artisan/math:vec3",
		"//artisan/math:mat",
		"//artisan/math:transform",
		"//artisan/math:stats",
		"//artisan/triangle/shader:simple-tga-shader",
		"//artisan/triangle/shader:phong-shader",
		"//artisan/triangle/shader:directional-light-shader",
		"//artisan/triangle/shader:color-and-light-shader",
		"//artisan/file:tga",
	],
	data = [
		"//artisan/assets:assets",
	]
)
