#pragma once
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_image_write.hpp"

#include <stdint.h>
#include <stdlib.h>


#define COLOR(R,G,B,A) (uint8_t)R | (uint8_t)G << 8 | (uint8_t)B << 16 | (uint8_t)A << 24
class Framebuffer {
public:
	Framebuffer(uint16_t width, uint16_t height) {
		Width = width;
		Height = height;
		Data = (uint32_t*)calloc(width * height, sizeof(uint32_t));
	}

	void SetPixel(uint16_t x, uint16_t y, uint32_t color) {
		if (x < 0 || y<0 || x>=Width || y >= Height) {
			return;
		}
		Data[x + Width * y] = color;
	}

	uint32_t GetPixel(uint16_t x, uint16_t y) {
		return Data[x + Width * y];
	}

	void Serialize(const char* path) {
		stbi_write_bmp(path, Width, Height, 4, Data);
	}

public:
	uint16_t Width, Height;
	uint32_t* Data;
};