# Ray Tracer

<p align="center">
  <img width="450" alt="ray-tracer" src="https://github.com/vqiu25/ray-tracer/assets/109129209/42dd2ed2-d84e-4892-baed-37525b095df4">
</p>

## About
A simplistic ray tracing engine, built with the guidance of Peter Shirley's "Ray Tracing in One Weekend" book. This is a rudimentary implementation that incorporates only spheres. However, this version utilises multithreading and a GUI, which were otherwise absent.

## Image
<p align="center">
  <img width="750" alt="image" src="https://github.com/vqiu25/ray-tracer/assets/109129209/8a800403-f803-456b-81f2-a4275c895bfb">
</p>

## Compilation
If SDL2 was installed using Homebew on MacOS:

`g++ -std=c++17 -I./include -I/opt/homebrew/include src/main.cpp -L/opt/homebrew/lib -lSDL2 -o ray_tracer`

## Running
`./ray-tracer`
