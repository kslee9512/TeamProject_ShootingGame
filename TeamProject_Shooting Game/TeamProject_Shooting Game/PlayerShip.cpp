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
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "초기화 실패", MB_OK);
		return E_FAIL;
	}

	// 미사일 매니저

	TargetManager::GetSingleton()->SetTarget(this);

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	moveSpeed = 150.0f;

	fireFrame = 0;
	frame = 2;

	ready = true;
	fire = false;
	lastUsed = 0;
	currFire = 0;
	hitBox = { 0, 0, 0, 0 };
	this->collisionChecker = collisionChecker;
	missileMgr = new MissileManager();
	missileMgr->PInit(collisionChecker, this);

	return S_OK;
}

void PlayerShip::Release()
{
	SAFE_RELEASE(missileMgr);
}

void PlayerShip::Update()
{
	currElapsed += TimerManager::GetSingleton()->GetElapsedTime();	// 현재 경과된 시간 1초 단위로 초기화
	lastUsed += TimerManager::GetSingleton()->GetElapsedTime();	// 마지막으로 사용한 키를 기준으로 경과 시간 검사 ( 하나라도 눌려있으면 0으로 계속 초기화 중)
	currFire += TimerManager::GetSingleton()->GetElapsedTime();

	Move();
	Fire();
	hitBox = GetRectToCenter(pos.x, pos.y, 35, 65);

	if (currElapsed >= 1.0f)	currElapsed = 0;

}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
		Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
		image->FrameRender(hdc, pos.x, pos.y, frame, 0, true);
		if (fire) fireImage->FrameRender(hdc, pos.x-2, pos.y-55, fireFrame, 0, true);
	}

	if (missileMgr)
	{
		missileMgr->Render(hdc);
	}
}

void PlayerShip::Move()
{
	if (lastUsed >= 1.0f)		// 키를 사용한 이력이 1초를 지나가면 다시 원상태로 복귀
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
		lastUsed = 0;

	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
		lastUsed = 0;
	}
}

void PlayerShip::Fire()
{
	if (missileMgr)
	{
		// 함수 호출 주기를 바꿔보자.
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
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