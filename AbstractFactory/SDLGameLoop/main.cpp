#include <SDL.h>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Factory.h"
#include "CharacterFactory.h"


using namespace std;
int main(int argc, char** argv)
{
	Factory* factory = new CharacterFactory;
	vector<Character*> characters;
	characters.push_back(factory->CreatePlayer());
	characters.push_back(factory->CreateOpponents());
	
	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->draw();
	}

	system("PAUSE");
	return 0;
}