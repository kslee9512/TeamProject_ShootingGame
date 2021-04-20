#include "CollisionChecker.h"
#include "Missile.h"
#include "Enemy.h"
#include "PlayerShip.h"

void CollisionChecker::CheckCollision()
{
		for (itlEnemys = lEnemys.begin(); itlEnemys != lEnemys.end(); itlEnemys++)
		{
			if ((*itlEnemys)->GetMovePatternEnd() != true)
			{
				for (itlPlayerMissiles = lPlayerMissiles.begin(); itlPlayerMissiles != lPlayerMissiles.end(); itlPlayerMissiles++)
				{
					if ((*itlPlayerMissiles)->GetAttackBox().top <= (*itlEnemys)->GetHitBox().bottom
						&& (*itlPlayerMissiles)->GetAttackBox().left <= (*itlEnemys)->GetHitBox().right
						&& (*itlPlayerMissiles)->GetAttackBox().right >= (*itlEnemys)->GetHitBox().left)
					{
						(*itlPlayerMissiles)->SetIsFired(false);
						
					}
				}
			}
		}
}

void CollisionChecker::CheckPlayerCollision(PlayerShip* player)
{
	for (itlEnemyMissiles = lEnemyMissiles.begin(); itlEnemyMissiles != lEnemyMissiles.end(); itlEnemyMissiles++)
	{
		if ((*player).GetPlayerHitBox().top <= (*itlEnemyMissiles)->GetAttackBox().bottom &&
			(*player).GetPlayerHitBox().left <= (*itlEnemyMissiles)->GetAttackBox().right &&
			(*player).GetPlayerHitBox().right >= (*itlEnemyMissiles)->GetAttackBox().left &&
			(*player).GetPlayerHitBox().bottom >= (*itlEnemyMissiles)->GetAttackBox().top)
		{
			(*itlEnemyMissiles)->SetIsFired(false);
			lEnemyMissiles.remove((*itlEnemyMissiles));
		}
	}
}
