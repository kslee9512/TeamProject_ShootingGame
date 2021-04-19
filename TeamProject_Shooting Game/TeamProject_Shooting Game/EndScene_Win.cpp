#include "EndScene_Win.h"
#include "Image.h":

HRESULT EndScene_Win::Init()
{
	endPhaseBG_Win = new Image();
	if (FAILED(endPhaseBG_Win->Init(endPhaseBG_Win_dir,
		endPhaseBG_size.x, endPhaseBG_size.y,
		1, 1,
		true, RGB(255, 0, 255))))
	{
		return E_FAIL;
	}

	return S_OK;
}

void EndScene_Win::Release()
{
	endPhaseBG_Win->Release();
	delete endPhaseBG_Win;
	endPhaseBG_Win = nullptr;
}

void EndScene_Win::Update()
{
}

void EndScene_Win::Render(HDC hdc)
{
	if (endPhaseBG_Win)
	{
		endPhaseBG_Win->Render(hdc);
	}
}
