#include "draw.h"
#include "tgaimage.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
  constexpr int width = 64;
  constexpr int height = 64;
  TGAImage framebuffer(width, height, TGAImage::RGB);

  std::srand(std::time({}));
  for (int i = 0; i < (1 << 24); i++) {
    int ax = rand() % width, ay = rand() % height;
    int bx = rand() % width, by = rand() % height;
    line(ax, ay, bx, by, framebuffer, rcolor());
  }

  framebuffer.write_tga_file("tests/output/perf_lines.tga");
  return 0;
}
