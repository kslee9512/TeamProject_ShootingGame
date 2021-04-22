#include "ItemManager.h"
#include "Item.h"

HRESULT ItemManager::Init(CollisionChecker* collisionChecker)
{
	this->collisionChecker = collisionChecker;

    vItems.resize(2);
    for (int i = 0; i < 2; i++)
    {
        vItems[i] = new Item;
        vItems[i]->Init(collisionChecker);
    }
	return S_OK;
}

void ItemManager::Release()
{

    for (itItems = vItems.begin(); itItems != vItems.end(); itItems++)
    {
        (*itItems)->Release();
        delete (*itItems);
        (*itItems) = nullptr;
    }
    vItems.clear();
}

void ItemManager::Update()
{
    currElapsed += TimerManager::GetSingleton()->GetElapsedTime();

    if (currElapsed>=15.0f)
    {
        currElapsed = 0;
        Create();
    }

   for (int i = 0; i < vItems.size(); i++)
   {

       if (vItems[i]->GetIsCreated())
       {
           vItems[i]->Update();
       }
   }
}

void ItemManager::Render(HDC hdc)
{
    for (int i = 0; i < vItems.size(); i++)
    {
        if (vItems[i]->GetIsCreated())
        {
            vItems[i]->Render(hdc);
        }
    }
}

void ItemManager::Create()
{
    srand(time(NULL));

    for (itItems = vItems.begin(); itItems != vItems.end(); itItems++)
    {
        float random = ((rand() % 8) + 1);

        if ((*itItems)->GetIsCreated() == false)
        {
            (*itItems)->SetIsCreated(true);
            (*itItems)->SetPos({random * 100 ,0.0f });
            break;
        }
    }
}
