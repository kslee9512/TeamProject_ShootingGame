#pragma once
#include "config.h"
#include "GameNode.h"

class Image;
class StartScene : public GameNode
{
private:
	Image* startPhaseBG;
	const char* startPhaseBG_dir = "Image/startPhaseBG.bmp";
	POINT startPhaseBG_size = { WINSIZE_X, WINSIZE_Y };

	Image* imgPushStart;
	const char* imgPushStart_dir = "Image/UI_PushStart.bmp";
	POINT imgPushStart_size = { 240, 42 };
	POINT imgPushStart_pos = { 540, 550 };

	int scenePage = 0;

	int waitTime = 0;
	int inputTime = -100;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};
