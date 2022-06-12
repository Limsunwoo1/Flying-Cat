#include "MainGame.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "Player.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include <iostream>
#include <windows.h>

// 깃허브에 프로젝트 추가할때 주의사항
// 저장소를 하나 새로 만들고 가장 처음으로 커밋하는건 .gitIgnore 파일을 먼저 커밋할것
// .gitIgnore 파일에 C++, 비주얼 스튜디오 등 정보를 넣어놓고 커밋해야 쓸데없는 파일들이 안올라간다
// 깃 이그노어 먼저 커밋하고 새로고침하면 cpp, h 등 필수적인 파일만 리스트에 잡힌다

// 과제 1. 
// 게임 중간에 여러 크기의 사각형 장애물이 있고 여러개의 고양이 아이콘 텍스쳐로 된 오브젝트가 있다
// 그리고 화면 중앙에 쥐 아이콘 텍스쳐로 된 오브젝트가 있다
// 마우스를 클릭하는 동안에는 모든 고양이 오브젝트는 쥐 오브젝트를 향해 움직인다
// 마우스를 클릭하는 동안 쥐 오브젝트는 마우스 커서 위치에 존재한다.
// 이때 고양이 오브젝트는 여러 크기의 사각형 장애물을 통과하지 못한다.

// 과제 2.
// 벽돌깨기
// 화면 비율이 상하로 길어야 함
// 게임 시작 버튼을 누르면 1스테이지로 넘어가고 화면 상단에는 블록들이 존재하고
// 하단에는 좌우로 움직이는 막대기가 있고
// 공을 튕겨서 블록을 전부 제거하는 게임
// 일단 블록의 hp는 한대 맞으면 부서진다고 가정하고
// 만약 여유가 된다면 hp가 존재하고 hp 상태에 따라서 블록의 상태가 변하게끔 ( 누가봐도 얘는 깨지겠다를 알수있게 )


CMainGame::CMainGame()
{

}

CMainGame::~CMainGame()
{
	// ====================================
	SelectObject(BackHdc, BitMap);
	DeleteObject(BackBitMap);
	DeleteDC(BackHdc);
	// ====================================

	//delete Player;
}

void CMainGame::Init(HWND InHwnd, HINSTANCE InHInstance)
{
	// ====================================
	HInstance = InHInstance;
	Hwnd = InHwnd;
	Hdc = GetDC(Hwnd);

	// 싱글턴들 초기화 구간
	CResourceManager::GetInstance()->Init(HInstance, Hdc);
	CTimerManager::GetInstance()->Init();
	CKeyManager::GetInstance()->Init();
	CSceneManager::GetInstance()->Init();
	CCollisionManager::GetInstance()->Init();
	CEventManager::GetInstance()->Init();
	//

	// 더블버퍼링
	BackHdc = CreateCompatibleDC(Hdc);
	BackBitMap = CreateCompatibleBitmap(Hdc, 1920, 1080);
	BitMap = (HBITMAP)SelectObject(BackHdc, BackBitMap);   
	// ====================================

	
}

void CMainGame::Logic()
{
	// ====================================
	CTimerManager::GetInstance()->Update();
	float deltaTime = CTimerManager::GetInstance()->GetDeltaTime();
	Update(deltaTime);
	Render();
	// ====================================

	// 모든 게임 로직이 끝난 후에 이벤트를 처리하고 새로 시작하도록
	CEventManager::GetInstance()->Update(deltaTime);
}

void CMainGame::Update(float InDeltaTime)
{
	// ====================================
	CKeyManager::GetInstance()->Update(InDeltaTime);
	CSceneManager::GetInstance()->Update(InDeltaTime);
	CCollisionManager::GetInstance()->Update(InDeltaTime);
	// ====================================

	// Render 되기 직전에 마지막 업데이트
	// ====================================
	CSceneManager::GetInstance()->LateUpdate(InDeltaTime);
	// ====================================
}

void CMainGame::Render()
{
	// ====================================
	Rectangle(BackHdc, 0, 0, 980, 680);

	CSceneManager::GetInstance()->Render(BackHdc);

	BitBlt(Hdc, 0, 0, 980, 680, BackHdc, 0, 0, SRCCOPY);
	// ====================================
}

