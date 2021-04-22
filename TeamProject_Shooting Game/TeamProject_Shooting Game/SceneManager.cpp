#include "SceneManager.h"
#include "StartScene.h"
#include "EndScene_Win.h"
#include "EndScene_Lose.h"
#include "KeyManager.h"

HRESULT SceneManager::Init()
{
	startScene = new StartScene();
	startScene->Init();

	endScene_Win = new EndScene_Win();
	endScene_Win->Init();

	endScene_Lose = new EndScene_Lose();
	endScene_Lose->Init();

	scenePage = 0;

	return S_OK;
}

void SceneManager::Release()
{
	SAFE_DELETE(startScene);
	SAFE_DELETE(endScene_Win);
	SAFE_DELETE(endScene_Lose);
}

void SceneManager::Update()
{
	startScene->Update();

	//test ¹öÆ°
	if (scenePage == 0 && KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		scenePage = 1;
	}

	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD0))
	//{
	//	scenePage = 0;
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD1))
	//{
	//	scenePage = 1;
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD2) || battlePhaseEnd_Win)
	//{
	//	scenePage = 2;
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD3) || battlePhaseEnd_Lose)
	//{
	//	scenePage = 3;
	//}
}

void SceneManager::Render(HDC hdc)
{

	if (startScene && scenePage == 0)
	{
		startScene->Render(hdc);
	}

	if (scenePage == 2)
	{
		endScene_Win->Render(hdc);
	}
	if (scenePage == 3)
	{
		endScene_Lose->Render(hdc);
	}
}
