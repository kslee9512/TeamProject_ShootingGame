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
			(*player).GetPlayerHitBox().bottom >= (*itlEnemyMissiles)->GetAttackBox().top)
		{
			(*player).SetIsPlayerDmg(true);
			(*itlEnemyMissiles)->SetIsFired(false);

			itlEnemyMissiles = lEnemyMissiles.erase(itlEnemyMissiles);
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
			(*player).GetPlayerHitBox().right >= (*itlItem)->GetAttackBox().left)
		{
			(*itlItem)->SetIsCreated(false);
			if ((*player).GetGun() < 2)	(*player).SetGun((*player).GetGun() + 1);
			itlItem = lItem.erase(itlItem);
		}

		else
		{
			itlItem++;
		}
	}
}
