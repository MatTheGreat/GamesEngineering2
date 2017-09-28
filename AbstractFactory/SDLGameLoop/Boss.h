#pragma once
#include <iostream>
#include "Character.h"

class Boss : public Character
{
	public :
		void draw()
		{
			std::cout << "Draw Boss" << std::endl;
		}
};
