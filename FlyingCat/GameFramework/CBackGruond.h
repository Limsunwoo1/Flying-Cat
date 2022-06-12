#pragma once
#include "Object.h"
class CBackGruond :
	public CObject
{
public:
	CBackGruond();
	CBackGruond(Vector2D InPosition, Vector2D InScale);
	~CBackGruond();
	virtual void Render(HDC InHdc) override;
};

