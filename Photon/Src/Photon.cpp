#include "GFX/Framebuffer.hpp"
#include "GFX/Rasterizer.h"
#include "MATH/SimpleMath.h"

#include <iostream>


int main(void)
{
	Framebuffer* fb = new Framebuffer(512, 512);
	Rasterizer* rs = new Rasterizer(fb);

	rs->ClearFramebuffer(COLOR(0,0,0,255));
	
	Triangle tris;
	tris.points[0] = Vector3(0, 0, 0);
	tris.points[1] = Vector3(256, 0, 0);
	tris.points[2] = Vector3(256, 256,0);
	rs->DrawTriangle(tris, COLOR(255, 255, 255, 255));
	fb->Serialize("D://Desktop//output.bmp");
}
