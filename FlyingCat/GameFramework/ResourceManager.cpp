#include "ResourceManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
	for (std::pair<string, CTexture*> textureInfo : TextureList)
		delete textureInfo.second;

	TextureList.clear();
}

void CResourceManager::Init(HINSTANCE InHInst, HDC InHdc)
{
	HInstance = InHInst;
	Hdc = InHdc;


	LoadTexture("Player",L"Texture/HanSukBong.bmp");
	LoadTexture("Bullet", L"Texture/BubbleBobblePart2Sheet12.bmp");
	LoadTexture("MONSTER", L"Texture/ChinaHater.bmp");
	LoadTexture("BACKGRUOND", L"Texture/LostARK2.bmp");	
	LoadTexture("Object", L"Texture/MineCraft.bmp");
}

CTexture* CResourceManager::LoadTexture(const string& InName, const wstring& InFilePath)
{
	CTexture* texture = FindTexture(InName);
	if (texture)
		return texture;

	texture = new CTexture;
	if (!texture)
		return nullptr;

	if (texture->LoadTexture(InName, HInstance, Hdc, InFilePath))
	{
		TextureList.emplace(make_pair(InName, texture));
	}
	else
	{
		delete texture;
		texture = nullptr;
	}

	return texture;
}

CTexture* CResourceManager::FindTexture(const string& InName)
{
	//find 에 실패하면 iter에는 end() 값이 담긴다
	auto iter = TextureList.find(InName);
	if (iter == TextureList.end())
		return nullptr;

	return iter->second;
}
