#pragma once
#include "GameNode.h"

class Image;
class Item;
class CollisionChecker;
class ItemManager : public GameNode
{
private:
	vector<Item*> vItems;
	vector<Item*>::iterator itItems;
	CollisionChecker* collisionChecker;

	Image* M_item;

public:
	HRESULT Init(CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Create();
};

