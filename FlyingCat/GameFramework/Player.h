#pragma once
#include "Object.h"
class CPlayer :
    public CObject
{
private:
    int      HP;
public:
    CPlayer();
    CPlayer(Vector2D InVector, Vector2D InScale);
    ~CPlayer();

    virtual void Update(float InDeltaTime) override;
    virtual void Collision(const CObject* InOtherObject) override;
    virtual void Render(HDC InHdc) override;
    virtual void LateUpdate(float InDeltaTime) override;

public:
    int& GetPlayerHP() { return HP; };
    void SetPlayerHP(int InHP) { HP = InHP; };
};

