#pragma once
#include "config.h"
#include "GameNode.h"

class Image;
class EndScene_Lose : public GameNode
{
private:
	Image* endPhaseBG_Lose;
	const char* endPhaseBG_Lose_dir = "Image/endingPhaseBG_Lose.bmp";
	POINT endPhaseBG_size = { WINSIZE_X, WINSIZE_Y };

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

