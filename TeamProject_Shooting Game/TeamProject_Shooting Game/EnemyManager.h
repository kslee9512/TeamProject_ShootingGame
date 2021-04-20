#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class CollisionChecker;
class EnemyManager : public GameNode
{
private:
	vector<Enemy*> vEnemys;
	CollisionChecker* collisionChecker;

	bool IsBossAlive;
public:
	HRESULT Init(CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);
	inline void SetIsBossAlive(bool IsBossAlive) { this->IsBossAlive = IsBossAlive; }
	inline bool GetIsBossAlive() { return this->IsBossAlive; }
};

