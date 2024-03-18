# Artisan GFX

![some images generated by artisan gfx](https://github.com/graphomancer/artisan-gfx/blob/main/artisan/imagesamples/collage.png?raw=true)

Artisan GFX is a self contained 3D graphics library written for educational purposes. At this time, Artisan GFX has support for rasterizing OBJ files using developer supplied shaders.

### Design goals

Artisan has the following design goals

- Provide support for rasterizing OBJ files with vertex and fragment shaders
- follow engineering best practices:
	- use the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
	- use the [bazel build system](https://bazel.build/) for  tracking of dependencies and ergonomic test setup/execution
	- have extensive test coverage
- Minimize external dependencies
	- At this time there are no external dependencies other than standard C++ libraries.
	- This is to provide maximal educational value to its author and anyone reading Artisan GFX
	- External dependancies may be added later to provide GPU support.

### Abstractions

##### Linear Algebra

Artisan GFX contains a bespoke linear algebra library. The core types of the library are `Vec<TypeName, Dimension>` and `Mat<TypeName, RowDimension, ColumnDimension>`, representing vectors and matrices of arbitrary type and dimension. 

These core types use operator overloading to support standard linear algebra operations. For convenience, the library also supports multiplying triangles by matricies - this operation multiplies each vertex of the triangle by the matrix, treating each vertex as a vector of appropriate dimension. 

The flexibility of the `Vec` and `Mat` types allows them to be used to represent vectors, points, and transformations in diverse scenarios such as: 

- a 2D canvas, using `Vec<int, 2>` and `Mat<int, 2, 2>` 
- RGB color, using `Vec<int, 3>` and `Mat<int, 3, 3>`
- world coordinates, using `Vec<double, 3>` and `Mat<double, 3, 3>`
- homogeneous coordinates using `Vec<double, 4>` and `Mat<double, 4, 4>`

Common Vector and Matrix types are aliased, for example `Vec3` represents `Vec<double, 3>` and `Mat3` represents `Mat<double, 3, 3>`

##### Triangles and Vertices

Artisan GFX represents triangles using the `Triangle<VertexSubtype>` type. Each `Triangle<VertexSubtype>` contains three `VertexSubtype` objects, each being a subtype of  `Vertex<Type, Dimension>`. The flexibility of the `Triangle` and `Vertex` types allows them to be used to represent triangles in diverse scenarios such as

- a 2D canvas, using `Triangle<Vertex<int, 3>>`
- world coordinates, using `Triangle<Vertex<double, 3>>`
- homogeneous coordinates, using `Triangle<Vertex<double, 4>>`

Each `Vertex<Type, Dimenson>` contains a `Vec<Type, Dimenson>` as well as a hashmap of string to double values called `Properties`. 

`Properties` is used to store information useful during shading - for example when parsing OBJ files, it stores `UV` coordinates under the key values `"vt_u"` and `"vt_v"`. Shader programmers can access and store any data they may need associated with verticies during vertex and fragment shading.

Common `Vertex` and `Triangle` types are aliased. For example `Vertex<double, 3>` is aliased to `Vertex3` and `Triangle<Vertex3>` is aliased to `Triangle3`.

There is also a vertex subtype called `CVertex` - short for Canvas Vertex. A `CVertex` is a `Vertex<int, 2>`, and also has a `double z` property. This is to represent triangle verticies on a canvas, with each vertex having a z value for z buffering. `Triangle<CVertex>` is aliased to `CTriangle`

##### File Formats

Artisan GFX has libraries for parsing `OBJ` and `TGA`, and writing 2D arrays of pixel data to `PPM` files. 

`TGA` files are parsed into a 2D array of RGBA values. 

`OBJ` files are parsed into an array of triangles. The vertices of each triangle have the following properties set from the contents of the `OBJ` file (see section on verticies for a description of vertex properties)

- `"vt_u"` and `"vt_v"` for UV coordinates
- `"vn_x"`, `"vn_y"`, `"vn_z"` for vertex normals
##### Shaders
Shaders are supported implementing the shader interface:

```
class Shader {
public:
        virtual CTriangle Vertex(Triangle3 &t) = 0;
        virtual Color Fragment(const Vec3 &barycentric_cords, CTriangle &t) = 0;
};
```

The Vertex shader takes as input a Triangle<Vertex<double, 3>> and transforms it into a CTriangle representing the triangle on a canvas. 

The fragment shader is responsible for coloring pixels in the CTriangle generated by the vertex shader, using the  barycentric coordinates of a pixel to color as input.

To clarify how shaders are used, below is the `canvas` code that applies shaders to a `Triangle3`, as parsed from an OBJ file.
```
void Canvas::ShadeTriangle(Shader& s, Triangle3& t) {
        Ctriangle ct = s.Vertex(t);
        BoundingBox bb = BoundingBoxOf(ct);
        for (int i = bb.top_left[0]; i < bb.bottom_right[0]; i++) {
                for (int j = bb.top_left[1]; j < bb.bottom_right[1]; j++) {
                        Vec<int, 2> bbox_loc({i, j});
                        Vec3 bary = BarycentricCords(bbox_loc, ct);
                        double z = bary * Vec3({ct.GetA().z, ct.GetB().z, ct.GetC().z});
                        if ( BarycentricIsInternal(bary) ) {
                                Color c = s.Fragment(bary, ct);
                                PutPixel(i, j, z, c);
                        }
                }
        }
}
```

##### Canvas

The `Canvas` represents a 2D array of pixels that can be drawn on, using a zbuffer for managing pixel depth. `Canvas` is an abstract class, defining common functions to be used accross any type of canvas. Some functions specified by `Canvas` are:

- `ShadeTriangle(Shader& s, Triangle3& t)` - applies `Shader& s` to `Triangle3 t` as described in the `Shader` section
- `PutPixel(const int x, const int y, const double z, const Color c)` - if `z` is greater than the zbuffer value at coordinate `(x,y)`, update the zbuffer with `z` and set the color value of the canvas to `c` at `(x, y)`
- `DrawLine(const int x0, const int y0, const int x1, const int y1, Color c)` Draws a line having color `c` between `(x0, y0)` and `(x1, y1)`

An implementation of `Canvas` called `PixelGridCanvas` is provided, drawing to an array of RGB pixels.


#### Code Map
Code is organized under the following directory structure:

- `assets`: directory containing assets such as obj and tga files
- `canvas`: contains `Canvas` class and its subtypes
- `file`: Functions for reading and writing to various image related file formats
- `math`: Linear algebra abstractions
- `triangle`: contains the `Vertex` and `Triangle` class
    - `shader`: contains `Shader` class and its subclasses
- `rasterizer`: contains `Rasterizer.cpp`, which ties together the above libraries to rasterize an example image.


#### Sources Consulted
- [tinyrenderer](https://github.com/ssloy/tinyrenderer).
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [Learning Modern 3D Graphics Programming](https://paroj.github.io/gltut/)
- [Computer Graphics From Scratch](https://gabrielgambetta.com/computer-graphics-from-scratch/)
