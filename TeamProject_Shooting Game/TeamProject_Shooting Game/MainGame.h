#pragma once
#include "GameNode.h"

class PlayerShip;
class Enemy;
class EnemyManager;
class Image;
class SceneManager;
class MainGame : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";

	Image* backBuffer;
	Image* bin;

	EnemyManager* enemyMgr;
	SceneManager* sceneMgr;

	PlayerShip* playerShip;

	//int scenePage;

public:
	HRESULT Init();		// 오버라이딩 : 다형성
	void Release();
	void Update();
	void Render();

	void CheckCollision();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

