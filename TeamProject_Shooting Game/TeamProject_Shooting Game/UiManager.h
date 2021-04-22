#pragma once
#include "config.h"
#include "Singleton.h"

class Score;
class UiManager : public Singleton<UiManager>
{
private:
	Score* score;
	//SBullet* sbullet;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

