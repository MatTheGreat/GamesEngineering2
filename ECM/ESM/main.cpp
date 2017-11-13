
#include <SDL.h>
#undef main

#include <iostream>
#include "Entity.h"
#include "HealthComponent.h"
#include "AISystem.h"
#include "PositionComponent.h"
#include "ControlComponent.h"
#include "ControlSystem.h"
#include "RenderSystem.h"



int main()
{
	SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Setup Health System
	AISystem aiSystem = AISystem();

	//Setup Render System
	RenderSystem renderSystem = RenderSystem();

	//Setup Control System
	ControlSystem controlSystem = ControlSystem();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Setup Player

	Entity* player = new Entity();

	//Create Health Component and Add to Player Entity
	HealthComponent* playerhealth = new HealthComponent();
	playerhealth->setHealth(100);
	player->addComponent(playerhealth);

	//Create Position Component and Add to Player Entity
	PositionComponent* playerPosition = new PositionComponent();
	playerPosition->setPosition(Position(25, 50));
	player->addComponent(playerPosition);

	//Create Control Component and Add to Player Entity
	ControlComponent* playerControl = new ControlComponent();
	playerControl->setKeyPressed(true);
	player->addComponent(playerControl);

	//Add Player Entity to Systems
	aiSystem.addEntity(player);
	renderSystem.addEntity(player);
	controlSystem.addEntity(player);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Setup Alien

	Entity* alien = new Entity();

	//Create Health Component and Add to Player Entity
	HealthComponent* alienhealth = new HealthComponent();
	alienhealth->setHealth(50);
	alien->addComponent(alienhealth);

	//Create Position Component and Add to Player Entity
	PositionComponent* alienPosition = new PositionComponent();
	alienPosition->setPosition(Position(200, 400));
	alien->addComponent(alienPosition);

	//Add Player Entity to Systems
	aiSystem.addEntity(alien);
	renderSystem.addEntity(alien);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Setup Dog

	Entity* dog = new Entity();

	//Create Health Component and Add to Player Entity
	HealthComponent* doghealth = new HealthComponent();
	doghealth->setHealth(15);
	dog->addComponent(doghealth);

	//Create Position Component and Add to Player Entity
	PositionComponent* dogPosition = new PositionComponent();
	dogPosition->setPosition(Position(150, 250));
	dog->addComponent(dogPosition);

	//Add Player Entity to Systems
	aiSystem.addEntity(dog);
	renderSystem.addEntity(dog);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Setup Cat

	Entity* cat = new Entity();

	//Create Health Component and Add to Player Entity
	HealthComponent* cathealth = new HealthComponent();
	cathealth->setHealth(25);
	cat->addComponent(cathealth);

	//Create Position Component and Add to Player Entity
	PositionComponent* catPosition = new PositionComponent();
	catPosition->setPosition(Position(175, 375));
	cat->addComponent(catPosition);

	//Add Player Entity to Systems
	aiSystem.addEntity(cat);
	renderSystem.addEntity(cat);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool running = true;
	while (running == true)
	{
		aiSystem.Update();
		renderSystem.Update();
		controlSystem.Update();

		SDL_Event Event;
		while(SDL_PollEvent(&Event))
		{
			
		}
	}
	system("PAUSE");
	return 0;
}