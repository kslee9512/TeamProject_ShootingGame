#pragma once
#include "GameNode.h"

class Image;
class Score : public GameNode
{
private:
	Image* score;
	const char* score_dir = "Image/Score.bmp";
	POINT score_size = { 1200, 342 };

	int currFrameX;
	float currElapsed;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

