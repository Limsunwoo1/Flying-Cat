#pragma once
#include <math.h>

// 과제1.
// 기존에 했던 고양이, 벽돌깨기에 노말벡터 도입하기

// 과제2.
// 태양계 만들기
// 실제 태양계처럼 크기를 할 필요는 없고
// 지구, 달, 태양 3가지가 있고
// 태양은 가만히 화면의 정중앙에 위치해있고
// 지구는 얼마 거리만큼 떨어져있고 달도 지구 기준으로 얼마 거리만큼 떨어져있다
// 달은 지구 주위를 공전하고
// 지구는 태양을 공전한다.

// 과제3.
// https://day-days.tistory.com/1117
// 모바일 게임 듀엣 모작해보기
// 장애물은 맘대로 해도 됨

typedef struct Vector2D {
	float x;
	float y;

	Vector2D() : x(0.f), y(0.f) {}
	Vector2D(float InX, float InY) : x(InX), y(InY) {}

	Vector2D operator* (float InValue) { return Vector2D(x * InValue, y * InValue); }

	Vector2D operator- (const Vector2D& InValue) { return Vector2D(x - InValue.x, y - InValue.y); }

	void operator+= (const Vector2D& InValue) {
		x = x + InValue.x;
		y = y + InValue.y;
	}

}Vector2D;

namespace UtilVector
{
	// 크기가 1로 정규화된 벡터는 노말벡터, 방향벡터, 단위벡터라고 한다.
	inline Vector2D Normalize(const Vector2D& InVector)
	{
		float length = sqrt((InVector.x * InVector.x) + (InVector.y * InVector.y));

		if (length != 0)
			return Vector2D(InVector.x / length, InVector.y / length);
		else
			return Vector2D(0.f, 0.f);
	}
}