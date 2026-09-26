# raytracerpp

A raytracer based on "Ray Tracing in One Weekend" with extended features, built in modern C++. 

My first project on GitHub, after studying RTOW. Experimenting for the first time with Git, CMake, external libraries 
and multithreading. Improving the efficiency of the raytracer and its architecture while modernizing and improving
its functions.


## Features from Ray Tracing in One Weekend
- Ray casting and rendering
- Sphere geometry
- Diffuse (matte) materials
- Metal materials with fuzziness
- Dielectric materials (glass/water)
- Anti-aliasing (multi-sampling)
- Camera positioning and field of view
- Defocus blur (depth of field)
- PPM image output

## My Extensions
- [x] PNG output format
  - [ ] Selection between PPM/PNG
- [x] CMake implementation
- [x] Multi-threading optimization
- [x] Performance timer
  - [x] Per-thread execution time reported on completion
- [ ] C++23 modernization

## Build
**Windows (CMD):**
```bash
g++ -o raytracerpp main.cpp -std=c++23
.\raytracerpp > output.ppm
```
The output will be saved as `output.ppm` in PPM format.

## Based On
[Ray Tracing in One Weekend](https://raytracing.github.io/)

## Third-Party Libraries
- [stb_image_write.h](https://github.com/nothings/stb) by Sean Barrett — used for PNG export (MIT License / public domain)

