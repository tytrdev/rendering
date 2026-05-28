#include "draw.h"
#include <cmath>
#include <cstdlib>
#include <utility>

float lerpf(float x, float y, float factor) {
  return ((1 - factor) * x) + (factor * y);
}

int lerpi(float x, float y, float factor) {
  return std::round(((1 - factor) * x) + (factor * y));
}

void line(int ax, int ay, int bx, int by, TGAImage &fb, TGAColor color) {
  bool steep = std::abs(ax - bx) < std::abs(ay - by);
  if (steep) {
    std::swap(ax, ay);
    std::swap(bx, by);
  }
  if (ax > bx) {
    std::swap(ax, bx);
    std::swap(ay, by);
  }

  int y = ay;
  int error = 0;
  for (int x = ax; x <= bx; x++) {
    if (steep) {
      fb.set(y, x, color);
    } else {
      fb.set(x, y, color);
    }
    error += 2 * std::abs(by - ay);
    if (error > bx - ax) {
      y += by > ay ? 1 : -1;
      error -= 2 * (bx - ax);
    }
  }
}

static uint8_t rb() { return static_cast<uint8_t>(std::rand() % 256); }
TGAColor rcolor() { return {rb(), rb(), rb(), rb()}; }

std::tuple<int, int> project(int width, int height, vec3 v) {
  return {static_cast<int>((v.x + 1.) * width / 2),
          static_cast<int>((v.y + 1.) * height / 2)};
}
