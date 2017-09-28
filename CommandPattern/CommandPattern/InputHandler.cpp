#include "SDL.h"
#include "InputHandler.h"
#include "MacroCommand.h"
#include "JumpCommand.h"
#include "FireCommand.h"


InputHandler::InputHandler()
{
}

InputHandler::InputHandler(Receiver* receiver)
{
	buttonA = SDLK_a;
	buttonB = SDLK_b;
	buttonA_ = new JumpCommand(receiver);
	buttonB_ = new FireCommand(receiver);
}

void InputHandler::handleInput(SDL_Event &event)
{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == buttonA)
			{
				buttonA_->execute();
			}
			if (event.key.keysym.sym == buttonB)
			{
				buttonB_->execute();
			}
		}
}