#pragma once
#include "Singleton.h"

class Enemy;
class PlayerShip;
class TargetManager : public Singleton<TargetManager>
{
private:

	Enemy* targetEnemy;

	PlayerShip* targetPlayer;


public:
	inline void SetTarget(PlayerShip* targetPlayer = nullptr)
	{
		this->targetPlayer = targetPlayer;
	}

	inline PlayerShip* GetTarget() { return this->targetPlayer; }

};

