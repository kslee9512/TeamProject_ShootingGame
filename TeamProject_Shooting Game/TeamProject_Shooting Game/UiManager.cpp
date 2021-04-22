#include "UiManager.h"
#include "Score.h"
#include "Number.h"
#include "ItemUI.h"

HRESULT UiManager::Init()
{
	score = new Score();
	score->Init();

	item = new ItemUI();
	item->Init();

	return S_OK;
}

void UiManager::Release()
{
	SAFE_DELETE(score);
	SAFE_DELETE(item);
	
}

void UiManager::Update()
{
	score->Update();
	item->Update(Special);
}

void UiManager::Render(HDC hdc)
{
	score->Render(hdc);
	item->Render(hdc);
}
