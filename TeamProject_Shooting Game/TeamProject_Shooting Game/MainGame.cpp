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
#include "ItemManager.h"
#include "UiManager.h"
HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();

	ImageManager::GetSingleton()->AddImage("Enemy",
		"Image/ufo.bmp", 530, 32, 10, 1,
		true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("EnemyMissile",
		"Image/구슬.bmp", 20, 20, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Team",
		"Image/rocket.bmp", 35, 42, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("scoreBullet",
		"Image/Score_Bullet.bmp", 18, 18, true, RGB(0, 0, 0));
	
	ImageManager::GetSingleton()->AddImage("Boss",
		"Image/보스frame.bmp", 3000, 300, 4, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Damage",
		"Image/화재.bmp", 300, 100, 4, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Destroy",
		"Image/폭발.bmp", 900, 200, 5, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Fire",
		"Image/Fire.bmp", 80, 35, 4, 1, true, RGB(0, 0, 0));

	ImageManager::GetSingleton()->AddImage("Move",
		"Image/MOVE.bmp", 350, 115, 5, 1, true, RGB(255, 255, 255));

	ImageManager::GetSingleton()->AddImage("PlayerMissile",
		"Image/bullet.bmp", 120, 26, 6, 1, true, RGB(0, 0, 0));

	ImageManager::GetSingleton()->AddImage("MissileItem",
		"Image/MS_Item.bmp", 210, 46, 5, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Special",
		"Image/Special.bmp", 252, 69, 4, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("SpecialItem",
		"Image/Special_Item.bmp", 210, 46, 5, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Score",
		"Image/Score.bmp", 181, 81, 6, 1, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Number",
		"Image/Number1.bmp", 270, 61, 10, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Life",
		"Image/life.bmp", 70, 55, 10, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Unlife",
		"Image/unlife.bmp", 70, 55, 10, 1, true, RGB(255, 0, 255));

<<<<<<< Updated upstream
=======
	ImageManager::GetSingleton()->AddImage("Bomb",
		"Image/Bomb.bmp", 264, 27, 11, 1, true, RGB(0, 0, 0));
>>>>>>> Stashed changes

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	stage = new Image();

	collisionChecker = new CollisionChecker();

	enemyMgr = new EnemyManager();
	enemyMgr->Init(collisionChecker);
	playerShip = new PlayerShip();
	playerShip->Init(collisionChecker);
	itemMgr = new ItemManager();
	itemMgr->Init(collisionChecker);

	sceneMgr = new SceneManager();
	sceneMgr->Init();

	uiMgr = new UiManager();
	uiMgr->Init();

	stageCnt = 1;	// stage 변경 변수
	scoreCnt = 0;

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
	SAFE_RELEASE(itemMgr);
	SAFE_RELEASE(uiMgr);
	delete collisionChecker;
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{

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

			if (itemMgr)
			{
				itemMgr->Update();
			}

			collisionChecker->CheckPlayerCollision(playerShip);
			collisionChecker->CheckCollision();		
			collisionChecker->CheckPlayerNoHit();

			if (uiMgr)
			{
				uiMgr->SetSpecial(enemyMgr->GetSpecial());
				uiMgr->Update();
			}

			if (enemyMgr->GetIsBossAlive() == false)
			{
				sceneMgr->SetBattlePhaseEnd_Win(true);
			}

			if (playerShip->GetIsPlayerAlive() == false)
			{
				sceneMgr->SetBattlePhaseEnd_Lose(true);
			}
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
			stage->MapRender(hBackDC, 1000);		// 기본 설정 1000
		}

		if (enemyMgr)
		{
			enemyMgr->Render(hBackDC);
		}

		if (playerShip)
		{
			playerShip->Render(hBackDC);
		}


		if (itemMgr)
		{
			itemMgr->Render(hBackDC);
		}

		if (uiMgr)
		{

			uiMgr->Render(hBackDC);
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
	TextOut(hBackDC, 20, 20, "MainGame 랜더 중", strlen("MainGame 랜더 중"));
	// ���콺 ��ǥ
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));
	// stage UI
	wsprintf(szText, "Stage : %d", stageCnt);
	TextOut(hBackDC, 20, 40, szText, strlen(szText));

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
