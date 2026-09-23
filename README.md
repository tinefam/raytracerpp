# raytracerpp

A ray tracing engine based on "Ray Tracing in One Weekend" with extended features, built in modern C++. 

My first project on github, after studying RTOW. Experimenting with Git,
external libraries and trying to improve the efficiency of the raytracer
while improving and modernizing its functions.


## Standard Features
- Ray casting and rendering
- Sphere geometry
- Diffuse (matte) materials
- Metal materials with fuzziness
- Dielectric materials (glass/water)
- Anti-aliasing (multi-sampling)
- Camera positioning and field of view
- Defocus blur (depth of field)
- PPM image output

## In Development
- [ ] PNG output format
    - [ ] Selection between PPM/PNG
- [X] Multi-threading optimization
- [X] Performance timer
  - [X] Per-thread timing breakdown on completion
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

