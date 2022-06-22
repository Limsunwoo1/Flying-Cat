#include "MonsterOBJ.h"
#include "CSceneManager.h"
#include "KeyManager.h"
#include "EventManager.h"
#include "TimerManager.h"
#include "CTexture.h"
#include <vector>

#define SPEED 200

MonsterOBJ::MonsterOBJ() : CObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
{

}

MonsterOBJ::MonsterOBJ(Vector2D InVector, Vector2D InScale) : CObject(Vector2D{ InVector.x , InVector.y }, Vector2D{ InScale.x, InScale.y })
{

}

MonsterOBJ::~MonsterOBJ()
{

}

void MonsterOBJ::Update(float InDeletaTime)
{
	  CObject::Update(InDeletaTime);
	  CObject* Player = CSceneManager::GetInstance()->Get_Object(OBJ_LAYER::PLAYER)[0];

	  if (KEY_STATE(KEY::LBUTTON) == KEY_STATE::HOLD)
	  {
		  Direction = Player->GetPosition() - Position;
		  Position += UtilVector::Normalize(Direction) * SPEED * InDeletaTime;
	  }
}

void MonsterOBJ::LateUpdate(float InDeltaTime)
{
	CObject::LateUpdate(InDeltaTime);
}

void MonsterOBJ::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);

	Vector2D InOtherPosition = InOtherObject->GetPosition();
	float DeletaTime = CTimerManager::GetInstance()->GetDeltaTime();
	if (InOtherPosition.x < Position.x)
	{
		Position.x += SPEED * DeletaTime;
	}
	else
	{
		Position.x -= SPEED * DeletaTime;
	}

	if (InOtherPosition.y < Position.y)
	{
		Position.y += SPEED * DeletaTime;
	}
	else
	{
		Position.y -= SPEED * DeletaTime;
	}
	//EventInfo eventInfo;
	//eventInfo.Type = EVENT_TYPE::DELETE_OBJECT;
	//eventInfo.Parameter = new OBJ_LAYER(OBJ_LAYER::MONSTER);
	//eventInfo.Parameter2 = this;
	//CEventManager::GetInstance()->AddEvent(eventInfo);
}

void MonsterOBJ::Render(HDC InHdc)
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