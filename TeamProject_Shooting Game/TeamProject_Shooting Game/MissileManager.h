#pragma once
#include "GameNode.h"

class Enemy;
class PlayerShip;
class Missile;
class CollisionChecker;
class MissileManager : public GameNode
{

private:

	vector<Missile*> vMissiles;
	vector<Missile*>::iterator itMissiles;
	CollisionChecker* collisionChecker;

	Enemy* owner;
	PlayerShip* Powner;

	bool Special;
	int cnt;
	float currElapsed;
	int gunLevel;

public:
	HRESULT Init(CollisionChecker* collisionChecker, Enemy* owner);
	HRESULT PInit(CollisionChecker* collisionChecker, PlayerShip* owner);
	void Release();
	void Update();
	void Render(HDC hdc);
	bool CheckIsFired();

	void Fire();
	void playerFire();
	inline void SetGun(int gunlevel) { this->gunLevel = gunlevel; }
};

