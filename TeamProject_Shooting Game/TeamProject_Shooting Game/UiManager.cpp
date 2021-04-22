#include "UiManager.h"
#include "Score.h"
#include "Number.h"
#include "ItemUI.h"
#include "PlayerHP.h"


HRESULT UiManager::Init()
{
	score = new Score();
	score->Init();

	item = new ItemUI();
	item->Init();

	number = new Number();
	number->Init();

	playerHp = new PlayerHP();
	playerHp->Init();

	return S_OK;
}

void UiManager::Release()
{
	SAFE_DELETE(score);

	SAFE_DELETE(item);

	SAFE_DELETE(number);
	SAFE_DELETE(playerHp);
}

void UiManager::Update()
{
	score->Update();

	item->Update(Special);

	number->Update();
	playerHp->Update();
}

void UiManager::Render(HDC hdc)
{
	score->Render(hdc);
	item->Render(hdc);
	number->Render(hdc);
	playerHp->Render(hdc);
}

