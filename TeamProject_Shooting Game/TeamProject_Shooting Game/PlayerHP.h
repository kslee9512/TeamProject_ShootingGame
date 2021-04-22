#pragma once
#include "GameNode.h"

class Image;
class PlayerHP : public GameNode
{
private:
	Image* life;
	const char* life_dir = "Image/life.bmp";
	Image* unlife;
	const char* unlife_dir = "Image/unlife.bmp";

	int playerCurrHP;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

