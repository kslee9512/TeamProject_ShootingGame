#pragma once
#include "GameNode.h"

class Image;
class CollisionChecker;
class Item : public GameNode
{
private:
	Image* itemImg;
	CollisionChecker* collisionChecker;

	FPOINT pos;
	RECT attackBox;
	int size;
	int frame;
	bool IsCreate;

	float currElapsed;
	float moveElapsed;

public:
	HRESULT Init(CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetIsCreated(bool IsCreate);

	inline bool GetIsCreated() { return this->IsCreate; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline RECT GetAttackBox() { return this->attackBox; }
};

