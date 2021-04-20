#include "MissileManager.h"
#include "TimerManager.h"
#include "Missile.h"
#include <random>
#include <iostream>
HRESULT MissileManager::Init(CollisionChecker* collisionChecker, Enemy* owner)
{
    this->owner = owner;
    this->collisionChecker = collisionChecker;
    vMissiles.resize(300);
    for (int i = 0; i < 300; i++)
    {
        vMissiles[i] = new Missile;
        vMissiles[i]->Init(collisionChecker, owner);
    }

    Special = false;
    cnt = 0;
    currElapsed = 0;

    return S_OK;
}

HRESULT MissileManager::PInit(CollisionChecker* collisionChecker, PlayerShip* owner)
{
	this->Powner = owner;
    this->collisionChecker = collisionChecker;
	vMissiles.resize(50);
	vector<Missile*>::iterator it;
	for (it = vMissiles.begin(); it != vMissiles.end(); it++)
	{
		(*it) = new Missile();
		(*it)->PInit(collisionChecker, this->Powner);

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
            else if (!Special)   vMissiles[i]->SetType(vMissiles[i]->Skill_02);
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

bool MissileManager::CheckIsFired()
{
    for (itMissiles = vMissiles.begin(); itMissiles != vMissiles.end(); itMissiles++)
    {
        if ((*itMissiles)->GetIsFired())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


void MissileManager::Fire()
{
    //for (itMissiles = vMissiles.begin(); itMissiles != vMissiles.end(); itMissiles++)
    //{
    //    if ((*itMissiles)->GetIsFired() == false && !Special)
    //    {
    //        (*itMissiles)->SetType(Missile::TYPE::Skill_01);
    //        (*itMissiles)->SetIsFired(true);
    //        (*itMissiles)->SetFireIndex(cnt);
    //        (*itMissiles)->SetAngle(DegToRad (-90));
    //        (*itMissiles)->SetTarget(TargetManager::GetSingleton()->GetTarget());
    //        cnt++;
    //        break;
    //    }
    //}
    //패턴2

    for (itMissiles = vMissiles.begin(); itMissiles != vMissiles.end(); itMissiles++)
    {
        if ((*itMissiles)->GetIsFired() == false && !Special)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<>dis(60, 120);
            
            (*itMissiles)->SetType(Missile::TYPE::Skill_02);
            (*itMissiles)->SetIsFired(true);
            (*itMissiles)->SetFireIndex(cnt);
            (*itMissiles)->SetAngle(-(DegToRad(dis(gen))));
            (*itMissiles)->SetTarget(TargetManager::GetSingleton()->GetTarget());
            cnt++;
            break;
        }
    }
}

void MissileManager::playerFire()
{
	for (itMissiles = vMissiles.begin(); itMissiles != vMissiles.end(); itMissiles++)
	{
		if ((*itMissiles)->GetIsFired() == false)
		{
			(*itMissiles)->SetIsFired(true);
			(*itMissiles)->SetAngle(DegToRad(90));
			break;
		}
	}
}