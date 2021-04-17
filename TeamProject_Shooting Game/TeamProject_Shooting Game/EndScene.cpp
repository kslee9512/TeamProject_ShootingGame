#include "EndScene.h"
#include "Image.h":

HRESULT EndScene::Init()
{
	endPhaseBG = new Image();
	if (FAILED(endPhaseBG->Init(endPhaseBG_dir,
		endPhaseBG_size.x, endPhaseBG_size.y,
		1, 1,
		true, RGB(255, 0, 255))))
	{
		return E_FAIL;
	}

	return S_OK;
}

void EndScene::Release()
{
	endPhaseBG->Release();
	delete endPhaseBG;
	endPhaseBG = nullptr;
}

void EndScene::Update()
{
}

void EndScene::Render(HDC hdc)
{
	if (endPhaseBG)
	{
		endPhaseBG->Render(hdc);
	}

}
