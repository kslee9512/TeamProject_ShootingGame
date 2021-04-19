#include "SceneManager.h"
#include "StartScene.h"
#include "EndScene.h"
#include "KeyManager.h"

HRESULT SceneManager::Init()
{
	startScene = new StartScene();
	startScene->Init();

	endScene = new EndScene();
	endScene->Init();

	scenePage = 0;

	return S_OK;
}

void SceneManager::Release()
{
	SAFE_DELETE(startScene);
	SAFE_DELETE(endScene);
}

void SceneManager::Update()
{
	startScene->Update();

	//test ¹öÆ°
	if (scenePage == 0 && KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		scenePage += 1;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD0))
	{
		scenePage = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD1))
	{
		scenePage = 1;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD2))
	{
		scenePage = 2;
	}
}

void SceneManager::Render(HDC hdc)
{

	if (startScene && scenePage == 0)
	{
		startScene->Render(hdc);
	}

	if (startScene && scenePage == 2)
	{
		endScene->Render(hdc);
	}
}
