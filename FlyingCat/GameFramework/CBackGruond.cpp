#include "CBackGruond.h"
#include "CTexture.h"
CBackGruond::CBackGruond()
{

}

CBackGruond::CBackGruond(Vector2D InPosition, Vector2D InScale) : CObject(Vector2D(InPosition.x, InPosition.y), Vector2D(InScale.x, InScale.y))
{
	this->SetObjectLayer(OBJ_LAYER::BACKGROUND);
}

CBackGruond::~CBackGruond()
{

}

void CBackGruond::Render(HDC InHdc)
{
	if (Texture)
	{
		// 32비트 bmp 는 bf.AlphaFormat = AC_SRC_ALPHA
		// 24비트 bmp 는 bf.AlphaFormat = 0

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = 255;

		AlphaBlend(InHdc,
			Position.x,
			Position.y,
			Scale.x,
			Scale.y,
			Texture->GetHdc(),
			0,
			0,
			Texture->GetWidth(),
			Texture->GetHeight(),
			bf);
	}
	else
	{
		Rectangle(InHdc,
			Position.x - (Scale.x * 0.5f),
			Position.y - (Scale.y * 0.5f),
			Position.x + (Scale.x * 0.5f),
			Position.y + (Scale.y * 0.5f));
	}
}