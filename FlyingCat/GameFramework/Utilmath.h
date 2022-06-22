#pragma once
#include <math.h>

#define PIE 3.141592

// 삼각함수 관련 주의사항
// sinf, cosf 등 삼각함수관련해서 들어가는 모든 인자는 라디안 값 ( Radian ) 이여야한다.
// 우리가 쓰는 0~360도 라는 단위는 10진법이라는 의미의 디그리 값 ( Degree )
// Radian 의 범위는 0 ~ 360도 가 0 ~ 2파이 까지로 표현된다.

// 0 ~ 180 도의 값이 => 0 ~ PIE 까지의 값으로 변환되는 식을 만든다고 할때
// 0 부터 시작하는 비례식을 짜는 방법은
// 특정변수/특정변수의 최대 값 * 비례되는 결과물의 최대값
// 
// 특정 수 부터 시작하는 비례식
// 0 부터 시작하게끔 비례식을 만들면 편함
// 특정변수/특정변수의 최대 값 * 비례되는 결과물의 최대값 + 비례되는 결과물의 최소값

// minX ~ maxX 의 값이 minY ~ maxY
// (X - minX) / (maxX - minX) * maxY + minY

namespace UtilMath
{
	inline float ToRaidan(float InDegree)
	{
		return InDegree / 180.f * PIE;
	}

	inline float ToDegree(float InRadian)
	{
		return InRadian * 180.f / PIE;
	}

	inline float Sin(float InDegree)
	{
		return sinf(ToRaidan(InDegree));
	}

	inline float Cos(float InDegree)
	{
		return cosf(ToRaidan(InDegree));
	}

	inline float Tan(float InDegree)
	{
		return tanf(ToRaidan(InDegree));
	}
}