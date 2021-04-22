#include "MissileManager.h"
#include "TimerManager.h"
#include "Missile.h"
#include <random>
#include <iostream>
HRESULT MissileManager::Init(CollisionChecker* collisionChecker, Enemy* owner)
{
    this->owner = owner;
    this->collisionChecker = collisionChecker;
    vMissiles.resize(500);
    for (int i = 0; i < 500; i++)
    {
        vMissiles[i] = new Missile;
        vMissiles[i]->Init(collisionChecker, owner);
    }

    Special = false;
    cnt = 0;
    currElapsed = 0;

    angleValue = 0;

    gunLevel = 0;

    return S_OK;
}

HRESULT MissileManager::PInit(CollisionChecker* collisionChecker, PlayerShip* owner)
{
	this->Powner = owner;
    this->collisionChecker = collisionChecker;
	vMissiles.resize(100);
	vector<Missile*>::iterator it;
	for (it = vMissiles.begin(); it != vMissiles.end(); it++)
	{
		(*it) = new Missile();
		(*it)->PInit(collisionChecker, this->Powner);
	}

    currElapsed = 0;
    angleValue = 0;
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
            else if (!Special)   vMissiles[i]->SetType(vMissiles[i]->Skill_02); //?´ë‹¹ë¶€ë¶??˜ì • ?„ìš”- ?˜ì •?˜ì? ?Šì„ ê²½ìš° ë¯¸ì‚¬?¼ì´ ?´ë‹¹ ?€?…ìœ¼ë¡?ê³ ì •??

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


void MissileManager::Fire(int randMissile)
{
    //?¨í„´1
    if (randMissile == 0)
    {
        for (itMissiles = vMissiles.begin(); itMissiles != vMissiles.end(); itMissiles++)
        {
            if ((*itMissiles)->GetIsFired() == false && !Special)
            {
                (*itMissiles)->SetType(Missile::TYPE::Skill_01);
                (*itMissiles)->SetIsFired(true);
                (*itMissiles)->SetFireIndex(cnt);
                (*itMissiles)->SetAngle(DegToRad(-90));
                (*itMissiles)->SetTarget(TargetManager::GetSingleton()->GetTarget());
                cnt++;
                break;
            }
        }
    }
    //?¨í„´2
    else if (randMissile == 1)
    {
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
    //?¨í„´3
    else if (randMissile == 2)
    {
        for (itMissiles = vMissiles.begin(); itMissiles != vMissiles.end(); itMissiles++)
        {
            if ((*itMissiles)->GetIsFired() == false && !Special)
            {
                (*itMissiles)->SetType(Missile::TYPE::Skill_03);
                (*itMissiles)->SetIsFired(true);
                (*itMissiles)->SetAngle(-(DegToRad(angleValue)));
                (*itMissiles)->SetTarget(TargetManager::GetSingleton()->GetTarget());
                angleValue += 5;
                if (angleValue >= 179)
                {
                    angleValue = 0;
                }
                break;
            }
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
	vector<Missile*>::iterator it;

    for (int i = 0; i <= gunLevel; i++)
    {
        for (it = vMissiles.begin(); it != vMissiles.end(); it++)
        {
            if ((*it)->GetIsFired() == false)
            {
                (*it)->SetIsFired(true);
                (*it)->SetAngle(DegToRad(90));
                if (i == 1)    (*it)->SetPos({ (*it)->GetPos().x - 50,(*it)->GetPos().y+50 });
                if (i == 2)    (*it)->SetPos({ (*it)->GetPos().x + 50,(*it)->GetPos().y + 50 });
                break;
            }
        }
    }
}