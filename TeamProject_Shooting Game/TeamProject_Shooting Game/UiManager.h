#pragma once
#include "config.h"
#include "Singleton.h"

class Score;
class Number;
class UiManager : public Singleton<UiManager>
{
private:
	Score* score;
	Number* number;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

