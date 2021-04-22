#pragma once
#include "GameNode.h"

// TODO : ��ĳ����, �ٿ�ĳ���� ����
class Image;
class MissileManager;
class TargetManager;
class CollisionChecker;
enum ENEMYSTATUS{ NONE, ENTERANCE, MOVE, FIRE, ENDSTATUS};
enum ENEMYTYPE { NORMAL, BOSS, ENDTYPE};
enum ENEMYDAMAGE { DESTROY, DAMAGE };
class Enemy : public GameNode
{
private:
	MissileManager* missileMgr;
	TargetManager* target;

	Image* image;
	Image* imageDmg;
	Image* imageDst;
	int currFrameX;
	int updateCount;
	float checkTimer;
	ENEMYSTATUS enemyStatus;
	ENEMYTYPE enemyType;
	ENEMYDAMAGE enemyDamage;
	FPOINT pos;
	int size;
	string name;
	RECT hitBox;
	int enterType;
	float moveSpeed;
	float angle;
	int dir;
	int verticalDir;
	bool isAlive;
	bool enterStage;
	bool endMovePattern;
	float changeStatusTimer;
	float currElapsed;
	float randElapsed;
	float randomX;
	float randomY;
	int randMissile;
	CollisionChecker* collisionChecker;
	int fireCount;

	int enemyCurrHP;
	int enemyDmg;
	bool IsEnemyDmg;
	bool IsCheckDmg;

	bool Special;

	bool IsBossAlive;

public:
	HRESULT BossInit(CollisionChecker* collisionChecker, int posX = 0, int posY = 0);
	HRESULT Init(CollisionChecker* collisionChecker, int posX = 0, int posY = 0);
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	void Enterance();
	void SlideEnterance_01();
	void SlideEnterance_02();
	void PointEnterance_01();
	void PointEnterance_02();
	void BossEnterance();
	void HorizonMove();
	void VerticalMove();

	// get, set
	inline void SetStatus(ENEMYSTATUS enemyStatus) { this->enemyStatus = enemyStatus; }
	inline void SetEnterType(int enterType) { this->enterType = enterType; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline int GetEnterType() { return this->enterType; }
	inline ENEMYSTATUS GetStatus() { return this->enemyStatus; }
	inline FPOINT GetPos() { return this->pos; }
	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
	inline RECT GetHitBox() { return this->hitBox; }
	inline bool GetMovePatternEnd() { return this->endMovePattern; }
	inline bool GetIsBossAlive() { return this->IsBossAlive; }

	inline void SetIsCheckDmg(bool IsCheckDmg) { this->IsCheckDmg = IsCheckDmg; }
	inline bool GetIsCheckDmg() { return this->IsCheckDmg; }
	inline void SetIsEnemyDmg(bool IsEnemyDmg) { this->IsEnemyDmg = IsEnemyDmg; }
	inline bool GetIsEnemyDmg() { return this->IsEnemyDmg; }
	inline void SetEnemyCurrHP(int enemyCurrHP) { this->enemyCurrHP = enemyCurrHP; }
	inline int GetEnemyCurrHP() { return this->enemyCurrHP; }
	inline void SetEnemyDmg(int enemyDmg) { this->enemyDmg = enemyDmg; }
	inline int GetEnemyDmg() { return this->enemyDmg; }

	inline void SetSpecial(bool Special) { this->Special = Special; }
	inline bool GetSpecial() { return this->Special; }

};

