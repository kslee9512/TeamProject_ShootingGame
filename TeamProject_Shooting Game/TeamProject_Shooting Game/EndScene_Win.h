#pragma once
#include "config.h"
#include "GameNode.h"

class Image;
class EndScene_Win : public GameNode
{
private:
	Image* endPhaseBG_Win;
	const char* endPhaseBG_Win_dir = "Image/endingPhaseBG_Win.bmp";
	POINT endPhaseBG_size = { WINSIZE_X, WINSIZE_Y };

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

