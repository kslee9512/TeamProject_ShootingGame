#pragma once
#include "GameNode.h"

class Image;
class MissileManager;
class CollisionChecker;
class PlayerShip : public GameNode
{
private:
	MissileManager* missileMgr;
	CollisionChecker* collisionChecker;
	Image* image;
	Image* fireImage;

	FPOINT pos;
	RECT hitBox;
	float moveSpeed;	// �ʴ� �̵��Ÿ�
	int frame;
	int fireFrame;
	bool ready;
	bool fire;

	float currElapsed;
	float lastUsed;		// Ű�� ������ ���� �ð�
	float currFire;		// �߻� �� ���̾� �̹���
	
public:
	HRESULT Init(CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);
	void Move();
	void Fire();

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline RECT GetPlayerHitBox() { return this->hitBox; }
	inline MissileManager* GetPlayerMgr() { return this->missileMgr; }
};

