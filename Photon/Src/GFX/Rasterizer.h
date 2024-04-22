#pragma once
#define NOMINMAX 

#include <algorithm>
#include <iostream>
#include "../MATH/SimpleMath.h"
#include "Framebuffer.hpp"

using namespace DirectX::SimpleMath;

#define ORTHO(v,side) (v + 1.0f)*side - side

struct Triangle {
	Vector3 points[3];
};


void Barycentric(Vector3 p, Vector3 a, Vector3 b, Vector3 c, float& u, float& v, float& w)
{
	Vector3 v0 = b - a;
	Vector3 v1 = c - a;
	Vector3 v2 = p - a;

	float den = v0.x * v1.y - v1.x * v0.y;
	v = (v2.x * v1.y - v1.x * v2.y) / den;
	w = (v0.x * v2.y - v2.x * v0.y) / den;
	u = 1.0f - v - w;
}

class Rasterizer {

public:
	Rasterizer(Framebuffer* fb) {
		m_frameBuffer = fb;
	}

	void ClearFramebuffer(uint32_t color) {
		for (int x = 0; x < m_frameBuffer->Width; x++) {
			for (int y = 0; y < m_frameBuffer->Height; y++) {
				m_frameBuffer->SetPixel(x, y, color);
			}
		}
	}
	void DrawLine(Vector3 a, Vector3 b, uint32_t color) {

		bool steep = false;
		if (std::abs(a.x - b.x) < std::abs(a.y - b.y)) {
			std::swap(a.x, a.y);
			std::swap(b.x, b.y);
			steep = true;
		}
		if (a.x > b.x) {
			std::swap(a.x, b.x);
			std::swap(a.y, b.y);
		}
		int dx = b.x - a.x;
		int dy = b.y - a.y;
		int derror2 = std::abs(dy) * 2;
		int error2 = 0;
		int y = a.y;
		for (int x = a.x; x <= b.x; x++) {
			if (steep) {
				m_frameBuffer->SetPixel(y, x, color);
			}
			else {
				m_frameBuffer->SetPixel(x, y, color);
			}
			error2 += derror2;
			if (error2 > dx) {
				y += (b.y > a.y ? 1 : -1);
				error2 -= dx * 2;
			}
		}
	}
	void DrawTriangle(Triangle triangle, uint32_t color) {
		Vector3 bboxmin;
		Vector3 bboxmax;
		
		bboxmin.x = std::min(triangle.points[0].x, std::min(triangle.points[1].x, triangle.points[2].x));
		bboxmin.y = std::min(triangle.points[0].y, std::min(triangle.points[1].y, triangle.points[2].y));

		bboxmax.x = std::max(triangle.points[0].x, std::max(triangle.points[1].x, triangle.points[2].x));
		bboxmax.y = std::max(triangle.points[0].y, std::max(triangle.points[1].y, triangle.points[2].y));

		Vector3 P;
		for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
			for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
				P.z = 0;
				float u, v, w;
				Barycentric(P, triangle.points[0], triangle.points[1], triangle.points[2], u, v, w);
				if (u < 0 || v < 0 || w < 0) continue;
				m_frameBuffer->SetPixel(P.x, P.y, color);
			}
		}
	}
private:
	Framebuffer* m_frameBuffer;
};