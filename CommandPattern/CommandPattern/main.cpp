
#include <SDL.h>
#undef main
#include "Command.h"
#include "InputHandler.h"
#include <iostream>


int main()
{
	SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	Receiver * receiver = new Receiver();
	InputHandler input;
	input = InputHandler(receiver);
	bool running = true;
	while (running == true)
	{
		SDL_Event Event;
		while(SDL_PollEvent(&Event))
		{
			input.handleInput(Event);
		}
	}
	system("PAUSE");
	return 0;
}