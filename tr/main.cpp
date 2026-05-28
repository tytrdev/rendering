#include "draw.h"
#include "model.h"
#include "tgaimage.h"
#include <iostream>

constexpr int W = 800;
constexpr int H = 800;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " obj/model.obj" << std::endl;
    return 1;
  }

  Model model(argv[1]);
  TGAImage framebuffer(W, H, TGAImage::RGB);

  for (int i = 0; i < model.nfaces(); i++) {
    auto [ax, ay] = project(W, H, model.vert(i, 0));
    auto [bx, by] = project(W, H, model.vert(i, 1));
    auto [cx, cy] = project(W, H, model.vert(i, 2));
    line(ax, ay, bx, by, framebuffer, red);
    line(ax, ay, cx, cy, framebuffer, red);
    line(bx, by, cx, cy, framebuffer, red);
  }

  framebuffer.write_tga_file("framebuffer.tga");
  return 0;
}
