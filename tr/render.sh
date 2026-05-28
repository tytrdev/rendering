#! /bin/bash

cmake --build build
build/tinyrenderer "${1:-obj/african_head/african_head.obj}"
magick framebuffer.tga png:- | chafa --format=kitty
