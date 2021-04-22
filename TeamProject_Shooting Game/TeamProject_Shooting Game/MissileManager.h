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
	int specialCnt;
	int cnt;
	float currElapsed;
	int angleValue;
	int gunLevel;

public:
	HRESULT Init(CollisionChecker* collisionChecker, Enemy* owner);
	HRESULT PInit(CollisionChecker* collisionChecker, PlayerShip* owner);
	void Release();
	void Update();
	void Render(HDC hdc);
	bool CheckIsFired();

	void Fire(int randMissile);
	void playerFire();
	inline void SetGun(int gunlevel) { this->gunLevel = gunlevel; }
	
	void SetSpecial(bool Special) { this->Special = Special; }
	bool GetSpecial() { return this->Special; }
	float GetTime() { return this->currElapsed; }

	inline void SetSpecialCnt(int specialCnt) { this->specialCnt = specialCnt; }
	inline bool GetSpecialCnt() { return this->specialCnt; }
};

