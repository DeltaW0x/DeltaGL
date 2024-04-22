#include <iostream>
#include <SDL.h>
#include "GFX/Framebuffer.hpp"
#include "GFX/Rasterizer.hpp"

#define WIDTH 512
#define HEIGHT 512
int main(int, char **)
{

    Framebuffer framebuffer(512, 512);
    Rasterizer rs(&framebuffer);
}
