#pragma once
#include "Player.h"
#include "Boss.h"
#include "Factory.h"

class CharacterFactory : public Factory
{
	public:
		Character* CreatePlayer()
		{
			return new Player;
		}
		Character* CreateOpponents()
		{
			return new Boss;
		}
};