#pragma once
#include "GameNode.h"

class Image;
class ItemUI : public GameNode
{
private:
	Image* item;
	Image* Cnt;
	POINT itemPos = { 950, 670 };

	int currFrameX;
	float currElapsed;
public:
	HRESULT Init();
	void Release();
	void Update(bool special);
	void Render(HDC hdc);
};

