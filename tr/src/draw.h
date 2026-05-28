#pragma once
#include "geometry.h"
#include "tgaimage.h"
#include <tuple>

constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

float lerpf(float x, float y, float factor);
int lerpi(float x, float y, float factor);

void line(int ax, int ay, int bx, int by, TGAImage &fb, TGAColor color);

TGAColor rcolor();

std::tuple<int, int> project(int width, int height, vec3 v);
