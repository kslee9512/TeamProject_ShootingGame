#pragma once
#include "GameNode.h"

class PlayerShip;
class Enemy;
class EnemyManager;
class Image;
class SceneManager;
class Missile;
class CollisionChecker;
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

	CollisionChecker* collisionChecker;

	Missile* missile;
	Enemy* enemy;
	//int scenePage;

public:
	HRESULT Init();		// 오버라이딩 : 다형성
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

