#include "EndScene_Lose.h"
#include "Image.h":

HRESULT EndScene_Lose::Init()
{
	endPhaseBG_Lose = new Image();
	if (FAILED(endPhaseBG_Lose->Init(endPhaseBG_Lose_dir,
		endPhaseBG_size.x, endPhaseBG_size.y,
		1, 1,
		true, RGB(255, 0, 255))))
	{
		return E_FAIL;
	}

	return S_OK;
}

void EndScene_Lose::Release()
{
	endPhaseBG_Lose->Release();
	delete endPhaseBG_Lose;
	endPhaseBG_Lose = nullptr;
}

void EndScene_Lose::Update()
{
}

void EndScene_Lose::Render(HDC hdc)
{
	if (endPhaseBG_Lose)
	{
		endPhaseBG_Lose->Render(hdc);
	}
}
