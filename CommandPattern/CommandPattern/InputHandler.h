#pragma once
#include "Command.h"
#include "Receiver.h"
#include <SDL.h>

class InputHandler
{
	public:
		InputHandler();
		InputHandler(Receiver* receiver);
		void handleInput(SDL_Event &event);

	private:
		Command* buttonA_;
		Command* buttonB_;

		SDL_Keycode buttonA;
		SDL_Keycode buttonB;

};