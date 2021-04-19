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
	for (itlEnemyMissiles = lEnemyMissiles.begin(); itlEnemyMissiles != lEnemyMissiles.end(); itlEnemyMissiles++)
	{
		if((*itlEnemyMissiles)->GetAttackBox().bottom >= (*player).GetPlayerRect().top &&
			(*itlEnemyMissiles)->GetAttackBox().left <= (*player).GetPlayerRect().right &&
			(*itlEnemyMissiles)->GetAttackBox().right >= (*player).GetPlayerRect().left)
		{
			(*itlEnemyMissiles)->SetIsFired(false);
		}
	}
}
