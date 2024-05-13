#include "ray.h"
#include "scene.h"
#include "sdltemplate.h"
#include "vec3.h"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex sdlMutex;

void renderSegment(int startY, int endY, int imageWidth, int imageHeight,
                   const vec3& lowerLeftCorner, const vec3& horizontal,
                   const vec3& vertical, const vec3& origin,
                   const vec3& sphereCentre, double sphere_radius) {
  for (int j = startY; j < endY; j++) {
    for (int i = 0; i < imageWidth; i++) {
      double u = double(i) / double(imageWidth);
      double v = double(j) / double(imageHeight);
      ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
      vec3 col = colour(r, sphereCentre, sphere_radius);
      int ir = int(255.999 * col.x());
      int ig = int(255.999 * col.y());
      int ib = int(255.999 * col.z());

      // Synchronise access to SDL drawing functions to prevent race conditions,
      // thus allowing only 1 thread to draw at a time
      {
        std::lock_guard<std::mutex> guard(sdlMutex);
        sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
        sdltemplate::drawPoint(i, imageHeight - j - 1);
      }
    }
  }
}

int main() {

  // 4:2 Aspect Ratio
  int imageWidth = 800;
  int imageHeight = 400;
  int numThreads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;

  // Print to terminal
  std::cout << "Format: P3 (colors in ASCII)\n";
  std::cout << "Dimensions: " << imageWidth << " x " << imageHeight << '\n';
  std::cout << "Max Color Value: 255\n";

  /*
  Visual Representation:
  * Camera at (0, 0, 0)

    (-2, 1, 1)  .-------.  (2, 1, 1)
                |       |
                |       |
  (-2, -1, -1)  .-------.  (2, -1, -1)

  */

  vec3 lowerLeftCorner = vec3(-2.0, -1.0, -1.0);
  vec3 horizontal = vec3(4.0, 0.0, 0.0);
  vec3 vertical = vec3(0.0, 2.0, 0.0);
  vec3 origin = vec3(0.0, 0.0, 0.0);
  vec3 sphereCentre(0, 0, -1);
  double sphere_radius = 0.5;

  sdltemplate::sdl("Ray Tracer", imageWidth, imageHeight);
  sdltemplate::loop();

  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  // Divide portions of the image by the number of threads to "distribute" the
  // workload
  int segmentHeight = imageHeight / numThreads;
  for (int t = 0; t < numThreads; t++) {
    int startY = t * segmentHeight;
    int endY = (t == numThreads - 1) ? imageHeight : (t + 1) * segmentHeight;
    threads.push_back(std::thread(
        renderSegment, startY, endY, imageWidth, imageHeight, lowerLeftCorner,
        horizontal, vertical, origin, sphereCentre, sphere_radius));
  }

  // Wait for all rendering threads to complete before proceeding
  for (auto& t : threads) {
    t.join();
  }

  // Stop timer
  auto stop = std::chrono::high_resolution_clock::now();

  // Calculate duration
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  std::cout << "Time taken for rendering: " << duration.count()
            << " milliseconds\n";

  while (sdltemplate::running) {
    sdltemplate::loop();
  }
}
