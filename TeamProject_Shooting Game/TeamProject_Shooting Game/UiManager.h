#pragma once
#include "config.h"
#include "Singleton.h"

class Score;
class ItemUI;
class Number;
class PlayerHP;
class UiManager : public Singleton<UiManager>
{
private:
	Score* score;
	Number* number;
	ItemUI* item;

	bool Special;
	int specialCnt = 3;

	PlayerHP* playerHp;

	int playerCurrHP = 3;
	int gameScore = 0;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetSpecial(bool Special) { this->Special = Special; }
	inline void SetSpecialCnt(int specialCnt) { this->specialCnt = specialCnt; }
	inline int GetSpecialCnt() { return this->specialCnt; }
	inline void SetPlayerCurrHP(int playerCurrHP) { this->playerCurrHP = playerCurrHP; }
	inline int GetPlayerCurrHP() { return this->playerCurrHP; }

	inline void SetScore(int gameScore) { this->gameScore = gameScore; }
	inline int GetScore() { return this->gameScore; }
};

