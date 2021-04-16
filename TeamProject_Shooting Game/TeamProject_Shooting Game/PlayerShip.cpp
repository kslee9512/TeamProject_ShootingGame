#include "PlayerShip.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT PlayerShip::Init()
{
	fireImage = ImageManager::GetSingleton()->AddImage("�÷��̾�߻�",
		"Image/Fire.bmp", 80, 35, 4, 1, true, RGB(0, 0, 0));
	image = ImageManager::GetSingleton()->AddImage("�÷��̾��̵�",
		"Image/MOVE.bmp", 350, 115, 5, 1, true, RGB(255, 255, 255));


	if (image == nullptr)
	{
		MessageBox(g_hWnd, "�÷��̾� ���ּ� �̹��� �ε� ����", "�ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// �̻��� �Ŵ���
	missileMgr = new MissileManager();
	missileMgr->PInit(this);

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	moveSpeed = 150.0f;

	fireFrame = 0;
	frame = 2;

	ready = true;
	fire = false;
	lastUsed = 0;
	currFire = 0;

	return S_OK;
}

void PlayerShip::Release()
{
	SAFE_RELEASE(missileMgr);
}

void PlayerShip::Update()
{
	currElapsed += TimerManager::GetSingleton()->GetElapsedTime();	// ���� ����� �ð� 1�� ������ �ʱ�ȭ
	lastUsed += TimerManager::GetSingleton()->GetElapsedTime();	// ���������� ����� Ű�� �������� ��� �ð� �˻� ( �ϳ��� ���������� 0���� ��� �ʱ�ȭ ��)
	currFire += TimerManager::GetSingleton()->GetElapsedTime();

	Move();

	if (missileMgr)
	{
		// �Լ� ȣ�� �ֱ⸦ �ٲ㺸��.
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

	if (currElapsed >= 1.0f)	currElapsed = 0;

}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
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
	if (lastUsed >= 1.0f)		// Ű�� ����� �̷��� 1�ʸ� �������� �ٽ� �����·� ����
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
		lastUsed = 0;

		if (frame > 0 && frame <= 2 && currElapsed >= 1.0f)
		{
			frame--;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{

		pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
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
