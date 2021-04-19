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
public:
	HRESULT Init(CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);

};

