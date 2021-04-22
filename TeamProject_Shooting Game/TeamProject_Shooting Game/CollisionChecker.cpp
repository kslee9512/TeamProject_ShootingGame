#include "CollisionChecker.h"
#include "Missile.h"
#include "Enemy.h"
#include "Item.h"
#include "PlayerShip.h"

void CollisionChecker::CheckCollision()
{
	for (itlEnemys = lEnemys.begin(); itlEnemys != lEnemys.end(); itlEnemys++)
	{
		if ((*itlEnemys)->GetMovePatternEnd() != true)
		{
			for (itlPlayerMissiles = lPlayerMissiles.begin(); itlPlayerMissiles != lPlayerMissiles.end(); )
			{
				if ((*itlPlayerMissiles)->GetAttackBox().top <= (*itlEnemys)->GetHitBox().bottom
					&& (*itlPlayerMissiles)->GetAttackBox().left <= (*itlEnemys)->GetHitBox().right
					&& (*itlPlayerMissiles)->GetAttackBox().right >= (*itlEnemys)->GetHitBox().left)
				{
					(*itlEnemys)->SetIsEnemyDmg(true);
					(*itlPlayerMissiles)->SetIsFired(false);
					itlPlayerMissiles = lPlayerMissiles.erase(itlPlayerMissiles);
				}
				else
				{
					itlPlayerMissiles++;
				}
			}
		}
	}
}

void CollisionChecker::CheckPlayerCollision(PlayerShip* player)
{
	for (itlEnemyMissiles = lEnemyMissiles.begin(); itlEnemyMissiles != lEnemyMissiles.end();)
	{
		if ((*player).GetPlayerHitBox().top <= (*itlEnemyMissiles)->GetAttackBox().bottom &&
			(*player).GetPlayerHitBox().left <= (*itlEnemyMissiles)->GetAttackBox().right &&
			(*player).GetPlayerHitBox().right >= (*itlEnemyMissiles)->GetAttackBox().left &&
			(*player).GetPlayerHitBox().bottom >= (*itlEnemyMissiles)->GetAttackBox().top &&
			!CheckPlayerHit)
		{
			if ((*itlEnemyMissiles)->GetType() != Missile::TYPE::FollowTarget)
			{
				(*player).SetIsPlayerDmg(true);
				(*itlEnemyMissiles)->SetIsFired(false);
				CheckPlayerHit = true;
				itlEnemyMissiles = lEnemyMissiles.erase(itlEnemyMissiles);
			}
			else if ((*itlEnemyMissiles)->GetType() == Missile::TYPE::FollowTarget)
			{
				(*itlEnemyMissiles)->SetIsFired(false);
				itlEnemyMissiles = lEnemyMissiles.erase(itlEnemyMissiles);
			}
		}
		else
		{
			itlEnemyMissiles++;
		}
	}

	for (itlItem = lItem.begin(); itlItem != lItem.end();)
	{
		if ((*player).GetPlayerHitBox().top <= (*itlItem)->GetAttackBox().bottom &&
			(*player).GetPlayerHitBox().left <= (*itlItem)->GetAttackBox().right &&
			(*player).GetPlayerHitBox().right >= (*itlItem)->GetAttackBox().left &&
			(*player).GetPlayerHitBox().bottom >= (*itlItem)->GetAttackBox().top)
		{
			(*itlItem)->SetIsCreated(false);
			if ((*itlItem)->GetItem() == 1 && (*player).GetGun() < 2)	(*player).SetGun((*player).GetGun() + 1);

			if ((*itlItem)->GetItem() == 2 && ((*player).GetSpecialCnt()) < 3)	(*player).SetSpecialCnt((*player).GetSpecialCnt() + 1 );
			(*itlItem)->SetItem(0);
			(*itlItem)->SetIsCreated(false);
			itlItem = lItem.erase(itlItem);
		}

		else
		{
			itlItem++;
		}
	}
}

void CollisionChecker::CheckPlayerNoHit()
{
	if (CheckPlayerHit == true)
	{
		damageTime += TimerManager::GetSingleton()->GetElapsedTime();

		if (damageTime >= 2)
		{
			CheckPlayerHit = false;
			damageTime = 0;
		}
	}
}
