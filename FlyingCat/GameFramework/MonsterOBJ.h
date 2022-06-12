#pragma once
#include "Object.h"

class MonsterOBJ :
    public CObject
{
private:
    bool    XPosition;
    bool    YPosition;

public:
    MonsterOBJ();
    MonsterOBJ(Vector2D InPosition, Vector2D InScale);
    ~MonsterOBJ();
    virtual void Update(float InDeletaTime) override;
    virtual void LateUpdate(float InDeltaTime) override;
    virtual void Render(HDC InHdc) override;

public:
    void Collision(const CObject* InOtherObject);
};

