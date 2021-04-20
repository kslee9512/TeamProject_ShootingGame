#pragma once
#include "GameNode.h"

class Image;
class Enemy;
class PlayerShip;
class CollisionChecker;
class Missile : public GameNode
{
public:
	enum TYPE { Normal, Skill_01, FollowTarget, End };
	enum FIRED { PLAYER, ENEMY, ENDFIRED };
private:
	Image* img;

	float moveSpeed;
	float moveTime;
	FPOINT pos;
	int size;
	RECT attackBox;
	int damage;
	float angle;
	bool isFired;
	TYPE missileType;
	int fireIndex;
	int fireStep;
	FIRED checkFired;
	//GameNode* target;
	PlayerShip* target;
	float destAngle;

	Enemy* owner;
	PlayerShip* Powner;
	CollisionChecker* collisionChecker;
	bool isPlayer;	//�÷��̾�� ���ʹ� �Ҹ� �̹��� ������ ���ؼ�
	int frame;
	float currElapsed;
	bool Special;		// Ư��ź �ߵ� ����

public:
	HRESULT Init(CollisionChecker* collisionChecker, Enemy* owner);
	HRESULT PInit(CollisionChecker* collisionChecker, PlayerShip* owner);
	void Release();
	void Update();
	void Render(HDC hdc);
	void MovingNormal();
	void MovingSkill_01();
	void MovingFollowTarget();
	void SetIsFired(bool isFired);

	inline FPOINT GetPos() { return this->pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline bool GetIsFired() { return this->isFired; }
	inline void SetTarget(PlayerShip* target) { this->target = target; }
	inline void SetType(TYPE type) { this->missileType = type; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
	inline void SetSpecial(bool special) { this->Special = special; }
	inline bool GetSpecial() { return this->Special; }
	inline int GetSize() { return this->size; }
	inline RECT GetAttackBox() { return this->attackBox; }
	inline void SetAttackBox(RECT attackBox) { this->attackBox = attackBox; }
};

