#pragma once
#include "config.h"
#include "GameNode.h"

class Image;
class EndScene : public GameNode
{
private:
	Image* endPhaseBG;
	const char* endPhaseBG_dir = "Image/endingPhaseBG.bmp";
	POINT endPhaseBG_size = { WINSIZE_X, WINSIZE_Y };

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};