#include "Number.h"
#include "Image.h"

HRESULT Number::Init()
{
	number = ImageManager::GetSingleton()->FindImage("Score");
	if (number == nullptr)
	{
		MessageBox(g_hWnd,
			"Score°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}

	currElapsed = 0.0f;

	return S_OK;
}

void Number::Release()
{
	number->Release();
	delete number;
	number = nullptr;
}

void Number::Update()
{
	currElapsed += TimerManager::GetSingleton()->GetElapsedTime();

	if (currElapsed >= 0.2f)
	{
		currFrameX++;
		if (currFrameX >= 6)
		{
			currFrameX = 0;
		}
		currElapsed = 0;
	}
}

void Number::Render(HDC hdc)
{
	if (number)
	{
		//score->Render(hdc);
		number->FrameRender(hdc, 40, 80, currFrameX, 0, true);
	}
}
