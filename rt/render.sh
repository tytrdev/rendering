#! /bin/bash
set -e

cmake --build build
build/raytracer >framebuffer.ppm

echo "" # force a new line

magick framebuffer.ppm png:- | chafa --format=kitty
