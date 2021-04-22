#pragma once
class Number
{
};

#pragma once
#include "GameNode.h"

class Image;
class Number : public GameNode
{
private:
	Image* number;
	const char* number_dir = "Image/Number.bmp";
	POINT number_size = { 1200, 342 };

	int currFrameX;
	float currElapsed;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};


