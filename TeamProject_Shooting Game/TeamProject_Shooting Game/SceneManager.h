#pragma once
#include "config.h"
#include "Singleton.h"

class StartScene;
class EndScene_Win;
class EndScene_Lose;
class SceneManager : public Singleton<SceneManager>
{
private:
	StartScene* startScene;
	EndScene_Win* endScene_Win;
	EndScene_Lose* endScene_Lose;

	int scenePage;
	
	bool battlePhaseEnd_Win;
	bool battlePhaseEnd_Lose;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetScenePage(int scenePage) { this->scenePage = scenePage; }
	inline int GetScenePage() { return this->scenePage; }
	inline void SetBattlePhaseEnd_Win(int battlePhaseEnd_Win) { this->battlePhaseEnd_Win = battlePhaseEnd_Win; }
	inline int GetBattlePhaseEnd_Win() { return this->battlePhaseEnd_Win; }
	inline void SetBattlePhaseEnd_Lose(int battlePhaseEnd_Lose) { this->battlePhaseEnd_Lose = battlePhaseEnd_Lose; }
	inline int GetBattlePhaseEnd_Lose() { return this->battlePhaseEnd_Lose; }
};




