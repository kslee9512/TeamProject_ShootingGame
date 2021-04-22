#include "ItemUI.h"
#include "Image.h"

HRESULT ItemUI::Init()
{
	item = ImageManager::GetSingleton()->FindImage("Special");
	if (item == nullptr)
	{
		MessageBox(g_hWnd,
			"itemUI FAIL!", "ERROR!", MB_OK);
		return E_FAIL;
	}

	Cnt = ImageManager::GetSingleton()->FindImage("Score");
	if (Cnt == nullptr)
	{
		MessageBox(g_hWnd,
			"Cnt FAIL!", "ERROR!", MB_OK);
		return E_FAIL;
	}

	currElapsed = 0.0f;
	currFrameX = 0;

	return S_OK;
}

void ItemUI::Release()
{
	item->Release();
	delete item;
	item = nullptr;

	Cnt->Release();
	delete Cnt;
	Cnt = nullptr;
}

void ItemUI::Update(bool special)
{
	if (special)
	{
		currElapsed += TimerManager::GetSingleton()->GetElapsedTime();

		if (currElapsed >= 1.0f)
		{
			currFrameX++;
			currElapsed = 0;
			if (currFrameX > 3)	currFrameX = 0;

		}
	}

	else if (!special)	currFrameX = 0;

}

void ItemUI::Render(HDC hdc)
{
	if (item)
	{
		//score->Render(hdc);
		item->FrameRender(hdc, itemPos.x, itemPos.y, currFrameX, 0, true);
	}
	if (Cnt)
	{
		Cnt->FrameRender(hdc, itemPos.x+50, itemPos.y, 0, 0, true);
	}
}
