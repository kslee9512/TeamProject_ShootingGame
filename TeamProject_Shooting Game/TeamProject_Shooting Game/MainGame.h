#pragma once
#include "GameNode.h"

class PlayerShip;
class Enemy;
class EnemyManager;
class Image;
class SceneManager;
class Missile;
class CollisionChecker;
class ItemManager;
class UiManager;
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

	Image* life;
	Image* losslife;

	Image* stage;

	EnemyManager* enemyMgr;
	SceneManager* sceneMgr;
	PlayerShip* playerShip;
	ItemManager* itemMgr;
	UiManager* uiMgr;

	CollisionChecker* collisionChecker;

	int stageCnt;
	int scoreCnt;

	Missile* missile;
	Enemy* enemy;

public:
	HRESULT Init();		// �������̵� : ������
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

