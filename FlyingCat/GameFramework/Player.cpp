#include "Player.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "ResourceManager.h"
#include "CTexture.h"
#include "EventManager.h"
#include "iostream"

CPlayer::CPlayer() : CObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
{
	HP = 3;
}

CPlayer::CPlayer(Vector2D InVector, Vector2D InScale) : CObject(Vector2D{ InVector.x , InVector.y }, Vector2D{ InScale.x, InScale.y })
{
	HP = 3;
}
 
CPlayer::~CPlayer()
{

}

void CPlayer::Update(float InDeltaTime)
{
	CObject::Update(InDeltaTime);

	PrevPosition = Position;

	if (KEY_STATE(KEY::W) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.y -= 1500 * InDeltaTime;

		if (position.y <= 20)
		{
			position.y = 20;
		}

		Position = position;
	}

	if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.x -= 1500 * InDeltaTime;

		if (position.x < 20)
		{
			position.x = 20;
		}

		Position = position;
	}

	if (KEY_STATE(KEY::S) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.y += 1500 * InDeltaTime;

		if (position.y > 620)
		{
			position.y = 620;
		}

		Position = position;
	}

	if (KEY_STATE(KEY::D) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.x += 1500 * InDeltaTime;

		if (position.x > 940)
		{
			position.x = 940;
		}

		Position = position;
	}

	if (KEY_STATE(KEY::LBUTTON) == KEY_STATE::HOLD)
	{
		POINT position = MOUSE_POS;

		Position.x = (float)position.x;
		Position.y = (float)position.y;
	}
}

void CPlayer::LateUpdate(float InDeltaTime)
{
	if (CurCollision)
		Position = PrevPosition;

	PrevCollision = CurCollision;
}

void CPlayer::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);

	/*EventInfo eventInfo;
	eventInfo.Type = EVENT_TYPE::DELETE_OBJECT;
	eventInfo.Parameter = new OBJ_LAYER(ObjLayer);
	eventInfo.Parameter2 = this;
	CEventManager::GetInstance()->AddEvent(eventInfo);*/
}

void CPlayer::Render(HDC InHdc)
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
			Position.x - (Texture->GetWidth() * 0.5f),
			Position.y - (Texture->GetHeight() * 0.5f),
			Texture->GetWidth(),
			Texture->GetHeight(),
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