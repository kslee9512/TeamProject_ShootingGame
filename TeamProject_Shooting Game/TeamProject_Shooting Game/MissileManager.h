#pragma once
#include "GameNode.h"
#include <vector>
#include <algorithm>
class Enemy;
class PlayerShip;
class Missile;
class CollisionChecker;
class MissileManager : public GameNode
{

private:

	vector<Missile*> vMissiles;
	vector<Missile*>::iterator itMissiles;

	Enemy* owner;
	PlayerShip* Powner;

	bool Special;
	int cnt;
	float currElapsed;
	int angleValue;
	CollisionChecker* collisionChecker;
public:
	HRESULT Init(CollisionChecker* collisionChecker, Enemy* owner);
	HRESULT PInit(CollisionChecker* collisionChecker, PlayerShip* owner);
	void Release();
	void Update();
	void Render(HDC hdc);
	bool CheckIsFired();

	void Fire(int randMissile);
	void playerFire();
};

