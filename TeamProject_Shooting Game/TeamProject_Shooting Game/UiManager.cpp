#include "UiManager.h"
#include "Score.h"
#include "Number.h"

HRESULT UiManager::Init()
{
	score = new Score();
	score->Init();

	number = new Number();
	number->Init();

	return S_OK;
}

void UiManager::Release()
{
	SAFE_DELETE(score);
	SAFE_DELETE(number);
}

void UiManager::Update()
{
	score->Update();
	number->Update();
}

void UiManager::Render(HDC hdc)
{
	score->Render(hdc);
	number->Render(hdc);
}
