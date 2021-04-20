#pragma once
#include <list>

using namespace std;

class Missile;
class PlayerShip;
class Enemy;
class CollisionChecker
{
private:
	// 플레이어 메모리주소
	PlayerShip* player;
	Enemy* enemy;

	// 활성화된 적들의 메모리주소 (EnemyMgr)
	list<Enemy*> lEnemys;
	list<Enemy*>::iterator itlEnemys;

	// 플레이어가 발사한 미사일들
	list<Missile*> lPlayerMissiles;
	list<Missile*>::iterator itlPlayerMissiles;
	// 적들이 발사한 미사일들
	list<Missile*> lEnemyMissiles;
	list<Missile*>::iterator itlEnemyMissiles;

public:

	void AddActiveEnemy(Enemy* enemy) { lEnemys.push_back(enemy); }
	void EraseDeadEnemy(Enemy* enemy) { lEnemys.remove(enemy); }

	void AddFiredEnemyMissile(Missile* missile) { lEnemyMissiles.push_back(missile); }
	void EraseEnemyMissile(Missile* missile) { lEnemyMissiles.remove(missile); }
	
	void AddFiredPlayerMissile(Missile* missile) { lPlayerMissiles.push_back(missile); }
	void ErasePlayerMissile(Missile* missile) { lPlayerMissiles.remove(missile); }

	void CheckCollision();
	void CheckPlayerCollision(PlayerShip* player);
};

