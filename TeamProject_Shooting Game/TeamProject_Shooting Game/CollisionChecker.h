#pragma once
#include <list>

using namespace std;

class Missile;
class PlayerShip;
class Enemy;
class Item;
class CollisionChecker
{
private:
	// �÷��̾� �޸��ּ�
	PlayerShip* player;
	Enemy* enemy;

	// Ȱ��ȭ�� ������ �޸��ּ� (EnemyMgr)
	list<Enemy*> lEnemys;
	list<Enemy*>::iterator itlEnemys;

	// �÷��̾ �߻��� �̻��ϵ�
	list<Missile*> lPlayerMissiles;
	list<Missile*>::iterator itlPlayerMissiles;
	// ������ �߻��� �̻��ϵ�
	list<Missile*> lEnemyMissiles;
	list<Missile*>::iterator itlEnemyMissiles;

	list<Item*> lItem;
	list<Item*>::iterator itlItem;

	bool CheckPlayerHit = false;
	float damageTime = 0.0f;
	int SpecialCnt;

public:
	void AddActiveEnemy(Enemy* enemy) { lEnemys.push_back(enemy); }
	void EraseDeadEnemy(Enemy* enemy) { lEnemys.remove(enemy); }

	void AddFiredEnemyMissile(Missile* missile) { lEnemyMissiles.push_back(missile); }
	void EraseEnemyMissile(Missile* missile) { lEnemyMissiles.remove(missile); }
	
	void AddFiredPlayerMissile(Missile* missile) { lPlayerMissiles.push_back(missile); }
	void ErasePlayerMissile(Missile* missile) { lPlayerMissiles.remove(missile); }

	void CheckCollision();
	void CheckPlayerCollision(PlayerShip* player);
	void CheckPlayerNoHit();
	
	inline void SetCheckPlayerHit(bool CheckPlayerHit) { this->CheckPlayerHit = CheckPlayerHit; }
	inline bool GetCheckPlayerHit() { return this->CheckPlayerHit; }
	inline void SetSpecialCnt(int SpecialCnt){ this->SpecialCnt = SpecialCnt; }
	inline bool GetSpecialCnt() { return this->SpecialCnt; }

	void AddItem(Item* item) { lItem.push_back(item); }
	void EraseItem(Item* item) { lItem.remove(item); }

};

