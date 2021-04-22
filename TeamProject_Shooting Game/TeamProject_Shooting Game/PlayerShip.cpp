#include "PlayerShip.h"
#include "Image.h"
#include "MissileManager.h"
#include "CommonFunction.h"
HRESULT PlayerShip::Init(CollisionChecker* collisionChecker)
{
	fireImage = ImageManager::GetSingleton()->FindImage("Fire");
	image = ImageManager::GetSingleton()->FindImage("Move");
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "Player Image Fail!", "ERROR!", MB_OK);

		return E_FAIL;
	}
	imageDst = ImageManager::GetSingleton()->FindImage("Destroy");
	if (imageDst == nullptr)
	{
		MessageBox(g_hWnd,
			"Player Destroy Image Fail!", "ERROR!", MB_OK);

		return E_FAIL;
	}

	team = ImageManager::GetSingleton()->FindImage("Team");

	// �̻��� �Ŵ���

	TargetManager::GetSingleton()->SetTarget(this);

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	moveSpeed = 300.0f;

	fireFrame = 0;
	frame = 2;
	currFrameX = 0;

	ready = true;
	fire = false;
	lastUsed = 0;
	currFire = 0;
	hitBox = { 0, 0, 0, 0 };
	this->collisionChecker = collisionChecker;
	missileMgr = new MissileManager();
	missileMgr->PInit(collisionChecker, this);


	playerCurrHP = 5;
	playerDmg = 1;

	IsPlayerAlive = true;
	IsPlayerDestroy = false;

	gunLevel = 0;

	return S_OK;
}

void PlayerShip::Release()
{
	SAFE_RELEASE(missileMgr);
}

void PlayerShip::Update()
{
	currElapsed += TimerManager::GetSingleton()->GetElapsedTime();	// ���� �����?�ð� 1�� ������ �ʱ�ȭ
	lastUsed += TimerManager::GetSingleton()->GetElapsedTime();	// ���������� �����?Ű�� �������� ���?�ð� �˻� ( �ϳ��� ���������� 0���� ���?�ʱ�ȭ ��)
	currFire += TimerManager::GetSingleton()->GetElapsedTime();

	//if (currElapsed >= 1.0f)	currElapsed = 0;

	if (!IsPlayerDestroy)
	{
		Move();
		Fire();
		hitBox = GetRectToCenter(pos.x, pos.y, 10, 10);
	}	


	if (currElapsed >= 1.0f)	
	{
		currFrameX++;
		if (currFrameX >= 4)
		{
			currFrameX = 0;
		}
		currElapsed = 0;
	}
}

void PlayerShip::Render(HDC hdc)
{
	if (IsPlayerDmg)
	{
		if ((missileMgr->GetSpecial()) == false)
		{
			//playerCurrHP -= playerDmg;
			IsPlayerDmg = false;
		}
	}

	if (image)
	{
		image->FrameRender(hdc, pos.x, pos.y, frame, 0, true);
		if (fire) fireImage->FrameRender(hdc, pos.x-2, pos.y-55, fireFrame, 0, true);

		if (playerCurrHP <= 0)
		{
			IsPlayerDestroy = true;
			imageDst->FrameRender(hdc, pos.x, pos.y, currFrameX + 1, 0, true);
			pos.y -= 0.1f;

			if (pos.y <= 300)
			{
				IsPlayerAlive = false;
			}
		}
		Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);

		if (gunLevel >= 1)
		{
			team->Render(hdc, pos.x - 50, pos.y + 40, true);
		}

		if (gunLevel == 2)	team->Render(hdc, pos.x + 50, pos.y + 40, true);
	}

	if (missileMgr)
	{
		missileMgr->Render(hdc);
	}
}

void PlayerShip::Move()
{
	if (lastUsed >= 1.0f)
	{
		if (frame > 2 && currElapsed >= 1.0f)
		{
			frame--;
			currElapsed = 0;
		}

		if (frame < 2 && currElapsed >= 1.0f)
		{
			frame++;
			currElapsed = 0;
		}
	}


	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
	{
		frame = 1;
		currElapsed = 0;
		ready = false;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
	{
		frame = 3;
		currElapsed = 0;
		ready = false;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
	{
		currElapsed = 0;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
	{
		currElapsed = 0;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{

		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		if (pos.x < 20)	pos.x = 20;

		lastUsed = 0;

		if (frame > 0 && frame <= 2 && currElapsed >= 1.0f)
		{
			frame--;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{

		pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		if (pos.x > WINSIZE_X-20)	pos.x = WINSIZE_X-20;

		lastUsed = 0;

		if (frame < 4 && frame >= 2 && currElapsed >= 1.0f)
		{
			frame++;
		}
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		if (pos.y <= 20) pos.y = 20;
		lastUsed = 0;

	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		if (pos.y >= WINSIZE_Y - 50) pos.y = WINSIZE_Y - 50;
		lastUsed = 0;
	}
}

void PlayerShip::Fire()
{
	if (missileMgr)
	{
		// �Լ� ȣ�� �ֱ⸦ �ٲ㺸��.
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			missileMgr->SetGun(gunLevel);
			fire = true;
			currFire = 0;
			missileMgr->playerFire();
		}

		missileMgr->Update();
	}

	if (fire && currFire >= 0.02f)
	{
		fireFrame++;
		currFire = 0;
		if (fireFrame > 3)
		{
			fireFrame = 0;
			fire = false;
		}
	}
}