cc_binary(
	name = "raytracer",
	srcs = ["RayTracer.cpp"],
	deps = [
		"//artisan/file:ppm",
		"//artisan/raytracer/geometry:sphere",
		"//artisan/raytracer/tracer:tracer",
		"//artisan/raytracer/material:lambertian",
		"//artisan/raytracer/material:metal"
	],
	data = [
		"//artisan/assets:assets",
	]
)
