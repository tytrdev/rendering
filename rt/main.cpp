#include "color.h"
#include <iostream>

constexpr int W = 256;
constexpr int H = 256;

int main() {

  std::cout << "P3\n" << W << ' ' << H << "\n255\n";

  for (int j = 0; j < H; j++) {
    std::clog << "\rScanlines remaining: " << (H - j) << ' ' << std::flush;

    for (int i = 0; i < W; i++) {
      auto pixel_color = color(double(i) / (W - 1), double(j) / (H - 1), 0);
      write_color(std::cout, pixel_color);
    }
  }
}
