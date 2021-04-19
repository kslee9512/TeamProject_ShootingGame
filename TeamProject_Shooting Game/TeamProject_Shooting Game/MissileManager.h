#pragma once
#include "GameNode.h"
#include <vector>
#include <algorithm>
class Enemy;
class PlayerShip;
class Missile;
class MissileManager : public GameNode
{
private:

	vector<Missile*> vMissiles;
	vector<Missile*>::iterator itMissiles;

	Enemy* owner;
	PlayerShip* Powner;

public:
	HRESULT Init(Enemy* owner);
	HRESULT PInit(PlayerShip* owner);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire();
	void playerFire();
};

