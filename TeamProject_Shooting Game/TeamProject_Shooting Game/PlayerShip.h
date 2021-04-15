#pragma once
#include "GameNode.h"

class Image;
class PlayerShip : public GameNode
{
private:
	Image* image;
	FPOINT pos;
	float moveSpeed;	// �ʴ� �̵��Ÿ�
	int frame;
	bool ready;

	float currElapsed;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

