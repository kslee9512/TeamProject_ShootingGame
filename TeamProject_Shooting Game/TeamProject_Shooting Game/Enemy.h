#pragma once
#include "GameNode.h"

// TODO : ��ĳ����, �ٿ�ĳ���� ����
class Image;
class MissileManager;
class TargetManager;
class CollisionChecker;
enum ENEMYSTATUS{ NONE, ENTERANCE, MOVE, FIRE, ENDSTATUS};
enum ENEMYTYPE { NORMAL, BOSS, ENDTYPE};
class Enemy : public GameNode
{
private:
	MissileManager* missileMgr;
	TargetManager* target;

	Image* image;
	int currFrameX;
	int updateCount;
	float checkTimer;
	ENEMYSTATUS enemyStatus;
	ENEMYTYPE enemyType;
	FPOINT pos;
	int size;
	string name;
	RECT hitBox;
	int enterType;
	float moveSpeed;
	float angle;
	int dir;
	bool isAlive;
	bool enterStage;
	bool endMovePattern;

	float currElapsed;

	CollisionChecker* collisionChecker;
	int fireCount;

public:
	HRESULT Init(CollisionChecker* collisionChecker, int posX = 0, int posY = 0);
	HRESULT BossInit(CollisionChecker* collisionChecker, int posX = 0, int posY = 0);
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
};

