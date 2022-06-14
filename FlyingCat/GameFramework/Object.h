#pragma once
#include "framework.h"

class CTexture;

enum class OBJ_LAYER : short {
	BACKGROUND		= 0,
	MONSTER			= 12,
	PLAYER			= 24,
	UI				= 30,
	MAX				= 32,
};

class CObject
{
private:
	static unsigned int Id;
	unsigned int ObjectId;
protected:
	Vector2D		Position;
	Vector2D		Scale;
	Vector2D		PrevPosition;
	Vector2D		CollisionScale; // 오브젝트 사이즈랑 동일하게 충돌을 설정할 필요가 없어서 별도로 설정
	OBJ_LAYER		ObjLayer;

	CTexture*		Texture;

	bool	PrevCollision;
	bool	CurCollision;
	bool	Othercollision;
public:
	CObject();
	CObject(Vector2D InPosition, Vector2D InScale);
	virtual ~CObject();

	virtual void Update(float InDeltaTime);
	virtual void LateUpdate(float InDeltaTime); // Render 되기 전 마지막 업데이트
	virtual void Render(HDC InHdc);

	virtual void Collision(const CObject* InOtherObject);

public:
	void SetTexture(CTexture* InTexture);

	void SetPosition(Vector2D InPosition) { Position = InPosition; }
	Vector2D GetPosition() const{ return Position; } 

	void SetScale(Vector2D InScale) { Scale = InScale; }
	Vector2D GetScale() { return Scale; }

	void SetCollisionScale(Vector2D InScale) { CollisionScale = InScale; }
	Vector2D GetCollisionScale() { return CollisionScale; }

	OBJ_LAYER GetObjectLayer() const;
	void SetObjectLayer(OBJ_LAYER InOBJ_Layer);

	bool GetCurCollision() { return CurCollision; };
	unsigned int GetId() const {return ObjectId;}
};

