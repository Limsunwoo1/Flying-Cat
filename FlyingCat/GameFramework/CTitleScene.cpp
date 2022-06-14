#include "CTitleScene.h"
#include "Button.h"
#include <string>
#include "Player.h"
#include "MonsterOBJ.h"
#include "Func.h"
#include "CSceneManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "UI.h"
#include "CBackGruond.h"
#include <random>
#include <iostream>

std::random_device Random;
CTitleScene::CTitleScene() 
{
}

CTitleScene::~CTitleScene()
{

}

void CTitleScene::Init()
{
	CObject* Player = new CPlayer();
	Player->SetObjectLayer(OBJ_LAYER::PLAYER);
	Player->SetPosition(Vector2D(500, 300));
	Player->SetTexture(CResourceManager::GetInstance()->FindTexture("Player"));
	AddObject(OBJ_LAYER::PLAYER, Player);

	CObject* Object = new CUI(Vector2D(200, 200), Vector2D(80, 80));
	Object->SetObjectLayer(OBJ_LAYER::UI);
	Object->SetTexture(CResourceManager::GetInstance()->FindTexture("Object"));
	AddObject(OBJ_LAYER::UI, Object);

	CObject* otherObject = new CUI(Vector2D(700,400), Vector2D(80,80));
	otherObject->SetObjectLayer(OBJ_LAYER::UI);
	otherObject->SetTexture(CResourceManager::GetInstance()->FindTexture("Object"));
	AddObject(OBJ_LAYER::UI, otherObject);

	CObject* Backgruond = new CBackGruond(Vector2D((float)0, (float)0), Vector2D((float)980, (float)680));
	Backgruond->SetTexture(CResourceManager::GetInstance()->FindTexture("BACKGRUOND"));
	AddObject(OBJ_LAYER::BACKGROUND,Backgruond);

	// UI는 충돌체크하면 로직이 꼬일수도 있음 체크해도 UI 끼리만 하도록 주의
	std::vector<OBJ_LAYER> checkLayerList;
	checkLayerList.push_back(OBJ_LAYER::UI);
	checkLayerList.push_back(OBJ_LAYER::MONSTER);

	CheckCollisionLayer[OBJ_LAYER::PLAYER] = checkLayerList;
	CheckCollisionLayer[OBJ_LAYER::UI] = checkLayerList;
	CheckCollisionLayer[OBJ_LAYER::MONSTER] = checkLayerList;
}

void CTitleScene::Clear()
{	
	CScene::Clear();
}

void CTitleScene::Update(float InDeltaTime)
{
	CScene::Update(InDeltaTime);

	AutoObjectAdd(InDeltaTime);
}

void CTitleScene::AutoObjectAdd(float InDeltaTime)
{
	std::mt19937 Gen(Random());
	std::uniform_int_distribution<int> XDis(0, 980);
	std::uniform_int_distribution<int> YDis(0, 680);

	static float CurDeltaTilme = 0.f;
	CurDeltaTilme += InDeltaTime;
	static int cnt = 0;

	if (CurDeltaTilme > 0.5)
	{
		if (cnt == 5)
			return;

		if ((XDis(Gen) % 2 == 0) && (YDis(Gen) % 2 == 0))
		{
			CObject* Monster = new MonsterOBJ(Vector2D(980, 680), Vector2D(50, 50));
			Monster->SetObjectLayer(OBJ_LAYER::MONSTER);
			Monster->SetTexture(CResourceManager::GetInstance()->FindTexture("MONSTER"));

			EventInfo newInfo;
			newInfo.Type = EVENT_TYPE::ADD_OBJECT;
			newInfo.Parameter = new OBJ_LAYER(OBJ_LAYER::MONSTER);
			newInfo.Parameter2 = Monster;
			CEventManager::GetInstance()->AddEvent(newInfo);
		}
		else if ((XDis(Gen) % 2 != 0) && (YDis(Gen) % 2 != 0))
		{
			CObject* Monster = new MonsterOBJ(Vector2D(0, 0), Vector2D(50, 50));
			Monster->SetObjectLayer(OBJ_LAYER::MONSTER);
			Monster->SetTexture(CResourceManager::GetInstance()->FindTexture("MONSTER"));

			EventInfo newInfo;
			newInfo.Type = EVENT_TYPE::ADD_OBJECT;
			newInfo.Parameter = new OBJ_LAYER(OBJ_LAYER::MONSTER);
			newInfo.Parameter2 = Monster;
			CEventManager::GetInstance()->AddEvent(newInfo);
		}
		else if ((XDis(Gen) % 2 != 0) && (YDis(Gen) % 2 == 0))
		{
			CObject* Monster = new MonsterOBJ(Vector2D(0, YDis(Gen)), Vector2D(50, 50));
			Monster->SetObjectLayer(OBJ_LAYER::MONSTER);
			Monster->SetTexture(CResourceManager::GetInstance()->FindTexture("MONSTER"));

			EventInfo newInfo;
			newInfo.Type = EVENT_TYPE::ADD_OBJECT;
			newInfo.Parameter = new OBJ_LAYER(OBJ_LAYER::MONSTER);
			newInfo.Parameter2 = Monster;
			CEventManager::GetInstance()->AddEvent(newInfo);
		}
		else
		{
			CObject* Monster = new MonsterOBJ(Vector2D(XDis(Gen), 0), Vector2D(50, 50));
			Monster->SetObjectLayer(OBJ_LAYER::MONSTER);
			Monster->SetTexture(CResourceManager::GetInstance()->FindTexture("MONSTER"));

			EventInfo newInfo;
			newInfo.Type = EVENT_TYPE::ADD_OBJECT;
			newInfo.Parameter = new OBJ_LAYER(OBJ_LAYER::MONSTER);
			newInfo.Parameter2 = Monster;
			CEventManager::GetInstance()->AddEvent(newInfo);
		}
		cnt++;
		CurDeltaTilme = 0.f;
	}
}