#include "Missile.h"
#include "Enemy.h"
#include "PlayerShip.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT Missile::Init(Enemy* owner)
{
	this->owner = owner;

	pos = {-100, -100};
	moveSpeed = 500.0f;
	moveTime = 10.0f;
	size = 50;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;
	isPlayer = false;
	whosType = ENEMY;

	// 이미지
	img = ImageManager::GetSingleton()->FindImage("EnemyMissile");
	if (img == nullptr)
	{
		MessageBox(g_hWnd,
			"EnemyMissile에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
		return E_FAIL;
	}

    return S_OK;
}

HRESULT Missile::PInit(PlayerShip* owner)
{
	this->Powner = owner;

	pos = { -100, -100 };
	moveSpeed = 5000.0f;
	moveTime = 10.0f;
	size = 50;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;
	isPlayer = true;
	frame = 0;
	currElapsed = 0;
	whosType = PLAYER;

	// 이미지
	img = ImageManager::GetSingleton()->FindImage("PlayerMissile");
	if (img == nullptr)
	{
		MessageBox(g_hWnd,
			"playerMissile에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Missile::Release()
{

}

void Missile::Update()
{
	// 위치 이동
	if (isFired)
	{
		currElapsed += TimerManager::GetSingleton()->GetElapsedTime();	// 현재 경과된 시간 1초 단위로 초기화

		if (currElapsed >= 0.02f)
		{
			frame++;
			currElapsed = 0;
			if (frame > 5)
				frame = 0;
		}

		switch (missileType)
		{
		case TYPE::Normal:
			MovingNormal();
			break;
		case TYPE::Skill_01:
			MovingSkill_01();
			break;
		case TYPE::FollowTarget:
			MovingFollowTarget();
			break;
		}

		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			isFired = false;
			fireStep = 0;
			currElapsed = 0;
			frame = 0;
		}
	}
}

void Missile::Render(HDC hdc)
{
	if (isFired)
	{
		if (!isPlayer)	img->Render(hdc, pos.x, pos.y, true);
		else if (isPlayer)	img->FrameRender(hdc, pos.x-12, pos.y, frame, 0);
		//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Missile::MovingNormal()
{
	float elapsedTime = TimerManager::GetSingleton()->GetElapsedTime();
	pos.x += cosf(angle) * moveSpeed * elapsedTime / moveTime;
	pos.y -= sinf(angle) * moveSpeed * elapsedTime / moveTime;
}

void Missile::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < 300.0f)
	{
		angle = fireIndex * 3.14f * 2.0f / 36.0f;
		fireStep++;
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingFollowTarget()
{
	if (target)
	{
		destAngle = GetAngle(pos, target->GetPos());
		float ratio = (destAngle - angle) / 50.0f;

		if (-0.01f < ratio && ratio < 0.01f)
		{
			angle = destAngle;
		}
		else
		{
			angle += ratio;
		}
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;

	if (owner)
	{
		pos.x = owner->GetPos().x;
		pos.y = owner->GetPos().y;
	}

	else if (Powner)
	{
		pos.x = Powner->GetPos().x;
		pos.y = Powner->GetPos().y-55;
	}
}
