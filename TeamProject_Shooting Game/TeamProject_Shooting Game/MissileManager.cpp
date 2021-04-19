#include "MissileManager.h"
#include "TimerManager.h"
#include "Missile.h"

HRESULT MissileManager::Init(Enemy* owner)
{
    this->owner = owner;

    vMissiles.resize(600);
    for (int i = 0; i < 600; i++)
    {
        vMissiles[i] = new Missile;
        vMissiles[i]->Init(owner);
    }

    Special = false;
    cnt = 0;
    currElapsed = 0;

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

    currElapsed = 0;

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
    currElapsed+= TimerManager::GetSingleton()->GetElapsedTime();

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD5))
    {
        currElapsed = 0;
        Special = true;
    }

    for (int i = 0; i < vMissiles.size(); i++)
    {
        if (owner)
        {
            if (Special) vMissiles[i]->SetType(vMissiles[i]->FollowTarget);
            else if (!Special)   vMissiles[i]->SetType(vMissiles[i]->Skill_01);
            vMissiles[i]->SetSpecial(Special);
        }

        vMissiles[i]->Update();
    }

    if (currElapsed >= 4.0f && Special)
    {
        Special = false;
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
        if ((*it)->GetIsFired() == false && !Special)
        {
            (*it)->SetIsFired(true);
            (*it)->SetFireIndex(cnt);
            (*it)->SetAngle(DegToRad (-90));    
            (*it)->SetTarget(TargetManager::GetSingleton()->GetTarget());
            cnt++;
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