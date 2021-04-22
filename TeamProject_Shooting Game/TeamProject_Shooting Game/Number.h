#include "GameNode.h"

class Image;
class Number : public GameNode
{
private:
	Image* number_100;
	const char* number_100_dir = "Image/Number.bmp";
	Image* number_10;
	const char* number_10_dir = "Image/Number.bmp";
	Image* number_1;
	const char* number_1_dir = "Image/Number.bmp";

	int scoreAdd;		// 점수를 추가해주는 변수
	int scorePlus;
	int scoreTenPlus;
	int scoreHundredPlus;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};


