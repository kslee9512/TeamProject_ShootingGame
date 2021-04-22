#pragma once
#include "config.h"
#include "Singleton.h"

class Score;
class Number;
class PlayerHP;
class UiManager : public Singleton<UiManager>
{
private:
	Score* score;
	Number* number;
	PlayerHP* playerHp;

	int playerCurrHP = 3;
	int gameScore = 0;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetPlayerCurrHP(int playerCurrHP) { this->playerCurrHP = playerCurrHP; }
	inline int GetPlayerCurrHP() { return this->playerCurrHP; }

	inline void SetScore(int gameScore) { this->gameScore = gameScore; }
	inline int GetScore() { return this->gameScore; }
};

