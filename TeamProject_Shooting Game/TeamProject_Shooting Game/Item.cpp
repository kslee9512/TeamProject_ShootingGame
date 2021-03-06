#include "Item.h"
#include "Image.h"
#include "CommonFunction.h"
#include "CollisionChecker.h"
#include "ItemManager.h"
HRESULT Item::Init(CollisionChecker* collisionChecker)
{
    this->collisionChecker = collisionChecker;

    itemImg = ImageManager::GetSingleton()->FindImage("MissileItem");
    if (itemImg == nullptr)
    {
        MessageBox(g_hWnd,
            "item가 로드안됨!", "실패!", MB_OK);
        return E_FAIL;
    }

    pos = { -100,-100 };
    attackBox = { 0, 0, 0, 0 };
    currElapsed = 0;
    itemType = 0;

	return S_OK;
}

void Item::Release()
{
}

void Item::Update()
{
    currElapsed += TimerManager::GetSingleton()->GetElapsedTime();
    moveElapsed += TimerManager::GetSingleton()->GetElapsedTime();

    if (itemType == 0)
    {
        srand(time(NULL));
        itemType = (rand() % 2) + 1;
    }
    
    if (IsCreate)
    {
        attackBox = GetRectToCenter(pos.x + 21, pos.y + 21, 25, 25);

        if (currElapsed >= 0.1f)
        {
            frame++;
            pos.y += 7.0f;
            currElapsed = 0;
            if (frame > 4)
                frame = 0;
        }

        if (pos.y >= WINSIZE_Y)
        {
            IsCreate = false;
            pos.x = -100;
            pos.y = -100;
            attackBox = { 0,0,0,0 };
            collisionChecker->EraseItem(this);
            itemType = 0;

        }

    }

}

void Item::Render(HDC hdc)
{
    if (IsCreate)
    {
        if (itemType == 1)   itemImg = ImageManager::GetSingleton()->FindImage("MissileItem");
        else if(itemType == 2)  itemImg = ImageManager::GetSingleton()->FindImage("SpecialItem");

        itemImg->FrameRender(hdc, pos.x, pos.y, frame, 0);
        //Rectangle(hdc, attackBox.left, attackBox.top, attackBox.right, attackBox.bottom);
    }
}

void Item::SetIsCreated(bool IsCreate)
{
    this->IsCreate = IsCreate; 

    if (IsCreate)
    {
        collisionChecker->AddItem(this);
    }
}
