#pragma once
#include "GameNode.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class MissileManager;
class TargetManager;
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
	RECT shape;
	int enterType;
	float moveSpeed;
	float angle;
	int dir;
	bool isAlive;
	bool enterStage;
	bool endMovePattern;

	int fireCount;

public:
	HRESULT Init(int posX = 0, int posY = 0);	
	HRESULT BossInit(int posX = 0, int posY = 0);
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
};

