#include "StartScene.h"
#include "Image.h":

HRESULT StartScene::Init()
{
	startPhaseBG = new Image();
	if (FAILED(startPhaseBG->Init(startPhaseBG_dir,
		startPhaseBG_size.x, startPhaseBG_size.y,
		1, 1,
		true, RGB(255, 0, 255))))
	{
		return E_FAIL;
	}

	imgPushStart = new Image();
	if (FAILED(imgPushStart->Init(imgPushStart_dir,
		imgPushStart_size.x, imgPushStart_size.y,
		true,
		RGB(255, 0, 255))))
	{
		return E_FAIL;
	}

	return S_OK;
}

void StartScene::Release()
{
	startPhaseBG->Release();
	delete startPhaseBG;
	startPhaseBG = nullptr;

	imgPushStart->Release();
	delete imgPushStart;
	imgPushStart = nullptr;
}

void StartScene::Update()
{
	waitTime++;

	/*if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		if (inputTime < 0)
		{
			inputTime = waitTime;
		}
	}*/
}

void StartScene::Render(HDC hdc)
{
	if (startPhaseBG)
	{
		startPhaseBG->Render(hdc);
	}

	if (inputTime < 0)
	{
		if (imgPushStart && (waitTime / 480) % 3 != 0)
		{
			imgPushStart->Render(hdc, imgPushStart_pos.x, imgPushStart_pos.y, true);
		}
	}
	else
	{
		if (imgPushStart && (waitTime / 2) % 40 == 20 && waitTime < inputTime + 400)
		{
			imgPushStart->Render(hdc, imgPushStart_pos.x, imgPushStart_pos.y, true);
		}
	}
}
