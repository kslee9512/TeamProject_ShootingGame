#include "MainGame.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Image.h"
#include "PlayerShip.h"

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

	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// ����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y); 

	bin = new Image();
	bin->Init("Image/Map01.bmp", WINSIZE_X, WINSIZE_Y);

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	playerShip = new PlayerShip();
	playerShip->Init();

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();

	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(bin);
	SAFE_RELEASE(enemyMgr);

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{

	float currTime1 = TimerManager::GetSingleton()->GetCurrTime();

	if (enemyMgr)
	{
		enemyMgr->Update();
	}

	if (playerShip)
	{
		playerShip->Update();
	}

	CheckCollision();
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	if (bin)
	{
		bin->MapRender(hBackDC, 1000);		// �ӵ� : �⺻ 1000
	}

	if (playerShip)
	{
		playerShip->Render(hBackDC);
	}

	if (enemyMgr)
	{
		enemyMgr->Render(hBackDC);
	}

	// �λ�
	TextOut(hBackDC, 20, 20, "MainGame ���� ��", strlen("MainGame ���� ��"));
	// ���콺 ��ǥ
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));
	// FPS
	TimerManager::GetSingleton()->Render(hBackDC);

	backBuffer->Render(hdc);
}

void MainGame::CheckCollision()
{
	// �� <-> ��ũ �̻��� 
	float distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int r1, r2;

	//for (int i = 0; i < enemyCount; i++)
	//{
	//	if (enemy[i].GetIsAlive() == false)	continue;

	//	for (int j = 0; j < tank->GetMissileCount(); j++)
	//	{
	//		if (missileArray[j].GetIsFired() == false)	continue;

	//		enemyPos = enemy[i].GetPos();
	//		missilePos = missileArray[j].GetPos();

	//		x = enemyPos.x - missilePos.x;
	//		y = enemyPos.y - missilePos.y;

	//		distance = sqrtf(x * x + y * y);

	//		r1 = enemy[i].GetSize() / 2;
	//		r2 = missileArray[j].GetSize() / 2;

	//		if (distance <= r1 + r2)
	//		{
	//			enemy[i].SetIsAlive(false);
	//			missileArray[j].SetIsFired(false);
	//			break;
	//		}
	//	}
	//}

	// �� <-> ��ũ

	// �� �̻��� <-> ��ũ

	// �� �̻��� <-> ��ũ �̻���
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
