#pragma once
#include "config.h"
#include "Singleton.h"

class Score;
class ItemUI;
class Number;
class UiManager : public Singleton<UiManager>
{
private:
	Score* score;
	Number* number;
	ItemUI* item;

	bool Special;
	int specialCnt = 3;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetSpecial(bool Special) { this->Special = Special; }
	inline void SetSpecialCnt(int specialCnt) { this->specialCnt = specialCnt; }
	inline int GetSpecialCnt() { return this->specialCnt; }
};

