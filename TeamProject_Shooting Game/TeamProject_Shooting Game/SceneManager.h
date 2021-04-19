#pragma once
#include "config.h"
#include "Singleton.h"

class StartScene;
class EndScene;
class SceneManager : public Singleton<SceneManager>
{
private:
	StartScene* startScene;
	EndScene* endScene;

	int scenePage;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetScenePage(int scenePage) { this->scenePage = scenePage; }
	inline int GetScenePage() { return this->scenePage; }
};




