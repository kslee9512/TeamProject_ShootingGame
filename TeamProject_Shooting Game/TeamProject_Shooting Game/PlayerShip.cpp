#include "PlayerShip.h"
#include "Image.h"

HRESULT PlayerShip::Init()
{
	image = ImageManager::GetSingleton()->AddImage("플레이어이동",
		"Image/MOVE.bmp", 350, 115, 5, 1, true, RGB(255, 255, 255));


	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "초기화 실패", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	moveSpeed = 150.0f;

	frame = 2;

	ready = true;

	return S_OK;
}

void PlayerShip::Release()
{
}

void PlayerShip::Update()
{
	currElapsed += TimerManager::GetSingleton()->GetElapsedTime();

	if (ready)
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

		if (frame>0 && frame <= 2 && currElapsed>=1.0f)
		{
			frame--;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{

		pos.x += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();

		if (frame<4 && frame >= 2 && currElapsed >= 1.0f)
		{
			frame++;
		}
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
	}

	if (currElapsed >= 1.0f)	currElapsed = 0;

}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
		image->FrameRender(hdc, pos.x, pos.y, frame, 0, true);
	}
}
