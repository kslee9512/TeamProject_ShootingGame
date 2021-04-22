#include "UiManager.h"
#include "Score.h"
#include "Number.h"

HRESULT UiManager::Init()
{
	score = new Score();
	score->Init();

	return S_OK;
}

void UiManager::Release()
{
	SAFE_DELETE(score);
}

void UiManager::Update()
{
	score->Update();
}

void UiManager::Render(HDC hdc)
{
	score->Render(hdc);
}
