#include "MainGame.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SceneManager.h"
#include "Missile.h"
#include "Image.h"
#include "PlayerShip.h"
#include "Enemy.h"
#include "MissileManager.h"
#include "CollisionChecker.h"
HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();

	// �̹����� �̸� �ε��Ѵ�
	ImageManager::GetSingleton()->AddImage("Enemy",
		"Image/ufo.bmp", 530, 32, 10, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("EnemyMissile",
		"Image/����.bmp", 20, 20, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Ư��ź",
		"Image/Score_Bullet.bmp", 18, 18, true, RGB(0, 0, 0));
	

	//ImageManager::GetSingleton()->AddImage("Boss",
	//	"Image/����.bmp", 700, 300, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Boss",
		"Image/����frame.bmp", 3000, 300, 4, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("�÷��̾�߻�",
		"Image/Fire.bmp", 80, 35, 4, 1, true, RGB(0, 0, 0));

	ImageManager::GetSingleton()->AddImage("�÷��̾��̵�",
		"Image/MOVE.bmp", 350, 115, 5, 1, true, RGB(255, 255, 255));

	ImageManager::GetSingleton()->AddImage("PlayerMissile",
		"Image/bullet.bmp", 120, 26, 6, 1, true, RGB(0, 0, 0));

	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// ����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	stage = new Image();

	collisionChecker = new CollisionChecker();

	enemyMgr = new EnemyManager();
	enemyMgr->Init(collisionChecker);
	playerShip = new PlayerShip();
	playerShip->Init(collisionChecker);

	sceneMgr = new SceneManager();
	sceneMgr->Init();

	stageCnt = 1;	// stage 변경 변수
	scoreCnt = 100;	// score 변수

	switch (stageCnt)
	{
	case 1:
		stage->Init("Image/Map01.bmp", WINSIZE_X, WINSIZE_Y);
		break;
	case 2:
		stage->Init("Image/Map02.bmp", WINSIZE_X, WINSIZE_Y);
		break;
	case 3:
		stage->Init("Image/Map03.bmp", WINSIZE_X, WINSIZE_Y);
		break;
	case 4:
		stage->Init("Image/Map04.bmp", WINSIZE_X, WINSIZE_Y);
		break;
	}

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();

	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(stage);
	SAFE_RELEASE(enemyMgr);
	SAFE_RELEASE(sceneMgr);
	delete collisionChecker;
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	float currTime1 = TimerManager::GetSingleton()->GetCurrTime();

	if (sceneMgr)
	{
		sceneMgr->Update();
		if (sceneMgr->GetScenePage() == 1)
		{
			if (enemyMgr)
			{

				enemyMgr->Update();
				
			}
			if (playerShip)
			{
				playerShip->Update();
			}
			collisionChecker->CheckCollision();
		}
	}
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	switch (sceneMgr->GetScenePage())
	{
	case 0:
		sceneMgr->Render(hBackDC);
		break;

	case 1:
		if (stage)
		{
			stage->MapRender(hBackDC, 1000);		// �ӵ� : �⺻ 1000
		}

		if (playerShip)
		{
			playerShip->Render(hBackDC);
		}

		if (enemyMgr)
		{
			enemyMgr->Render(hBackDC);
		}
		break;

	case 2:
		sceneMgr->Render(hBackDC);
		break;

	case 3:
		sceneMgr->Render(hBackDC);
		break;

	default:
		break;
	}

	//SetBkMode(hBackDC, TRANSPARENT);
	// �λ�
	TextOut(hBackDC, 20, 20, "MainGame ���� ��", strlen("MainGame ���� ��"));
	// ���콺 ��ǥ
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));
	// stage UI
	wsprintf(szText, "Stage : %d", stageCnt);
	TextOut(hBackDC, 20, 40, szText, strlen(szText));
	// score UI
	wsprintf(szText, "Score : %d", scoreCnt);
	TextOut(hBackDC, 20, 60, szText, strlen(szText));

	// FPS
	TimerManager::GetSingleton()->Render(hBackDC);

	backBuffer->Render(hdc);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
