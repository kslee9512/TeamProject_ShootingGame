#pragma once
#include "GameNode.h"

class PlayerShip;
class Enemy;
class EnemyManager;
class Image;
class SceneManager;
class Missile;
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
	Image* stage;

	EnemyManager* enemyMgr;
	SceneManager* sceneMgr;

	PlayerShip* playerShip;
	Enemy* enemy;
	
	PlayerShip* missile;  // �ΰ��� �����ѹ� 
	
	Enemy* boss;
	
	Missile* playerMis;

	RECT PlayerHitBox;
	RECT PlayeratkBox;
	RECT EnemyHitBox;
	RECT EnemymissileatkBox;
	
	RECT BossHitBox;
	int stageCnt;
	int scoreCnt;

public:
	HRESULT Init();		// �������̵� : ������
	void Release();
	void Update();
	void Render();

	void CheckCollision();
	
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

