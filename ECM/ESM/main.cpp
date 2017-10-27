
#include <SDL.h>
#undef main

#include <iostream>
#include "Entity.h"
#include "HealthComponent.h"
#include "HealthSystem.h"



int main()
{
	SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);

	HealthComponent playerhealth = HealthComponent();
	HealthSystem healthSystem = HealthSystem();
	Entity player = Entity();

	player.addComponent(playerhealth);
	healthSystem.addEntity(player);
	
	bool running = true;
	while (running == true)
	{
		healthSystem.Update();

		SDL_Event Event;
		while(SDL_PollEvent(&Event))
		{
			
		}
	}
	system("PAUSE");
	return 0;
}