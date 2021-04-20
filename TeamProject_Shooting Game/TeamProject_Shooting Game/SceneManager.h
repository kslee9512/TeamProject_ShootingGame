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
	
	bool battlePhaseEnd;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetScenePage(int scenePage) { this->scenePage = scenePage; }
	inline int GetScenePage() { return this->scenePage; }
	inline void SetBattlePhaseEnd(int battlePhaseEnd) { this->battlePhaseEnd = battlePhaseEnd; }
	inline int GetBattlePhaseEnd() { return this->battlePhaseEnd; }
};




