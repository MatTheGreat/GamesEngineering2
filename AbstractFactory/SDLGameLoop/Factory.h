#pragma once
#include "Character.h"

class Factory
{
	public:
		virtual Character* CreatePlayer() = 0;
		virtual Character* CreateOpponents() = 0;
};