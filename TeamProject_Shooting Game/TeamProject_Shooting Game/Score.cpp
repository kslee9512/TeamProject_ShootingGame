#include "Score.h"
#include "Image.h"

HRESULT Score::Init()
{
	score = ImageManager::GetSingleton()->FindImage("Score");
	if (score == nullptr)
	{
		MessageBox(g_hWnd,
			"Score°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}

	currElapsed = 0.0f;

	return S_OK;
}

void Score::Release()
{
	score->Release();
	delete score;
	score = nullptr;
}

void Score::Update()
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

void Score::Render(HDC hdc)
{
	if (score)
	{
		//score->Render(hdc);
		score->FrameRender(hdc, 40, 80, currFrameX, 0, true);
	}
}
