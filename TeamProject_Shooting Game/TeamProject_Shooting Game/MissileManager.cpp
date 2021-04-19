#include "MissileManager.h"
#include "Missile.h"
#include "PlayerShip.h"

HRESULT MissileManager::Init(Enemy* owner)
{
    this->owner = owner;

    vMissiles.resize(300);
    for (int i = 0; i < 300; i++)
    {
        vMissiles[i] = new Missile;
        vMissiles[i]->Init(owner);
    }


    return S_OK;
}

HRESULT MissileManager::PInit(PlayerShip* owner)
{
	this->Powner = owner;

	vMissiles.resize(50);
	vector<Missile*>::iterator it;
	for (it = vMissiles.begin(); it != vMissiles.end(); it++)
	{
		(*it) = new Missile();
		(*it)->PInit(this->Powner);

		// �̻��� �Ŵ����� ��� �ִ� �� ��ü�� ������ ����
	}
    
    
	return S_OK;
}

void MissileManager::Release()
{
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        (*it)->Release();
        delete (*it);
        (*it) = nullptr;
    }
    vMissiles.clear();
}

void MissileManager::Update()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Update();
    }

    //vector<Missile*>::iterator it;
    //for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    //{
    //    (*it)->Update();
    //}
}

void MissileManager::Render(HDC hdc)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        
        vMissiles[i]->Render(hdc);
    }
    
    //vector<Missile*>::iterator it;
    //for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    //{
    //    (*it)->Render(hdc);
    //}
}

void MissileManager::Fire()
{
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        if ((*it)->GetIsFired() == false)
        {
            (*it)->SetIsFired(true);
            (*it)->SetAngle(DegToRad (-90));            
            
            break;
        }
    }

}




void MissileManager::playerFire()		// ������ Ÿ������ Enemy�� Player�� �����ϰ� ���� ���� �̻��� ����ڿ� ��ĥ �� ���� ���ɼ�
{
	vector<Missile*>::iterator it;
	for (it = vMissiles.begin(); it != vMissiles.end(); it++)
	{
		if ((*it)->GetIsFired() == false)
		{
			(*it)->SetIsFired(true);
			(*it)->SetAngle(DegToRad(90));
			break;
		}
	}
}