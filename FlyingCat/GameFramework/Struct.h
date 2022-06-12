#pragma once

typedef struct Vector2D {
	float x;
	float y;

	Vector2D() : x(0.f), y(0.f) {}
	Vector2D(float InX, float InY) : x(InX), y(InY) {}

}Vector2D;