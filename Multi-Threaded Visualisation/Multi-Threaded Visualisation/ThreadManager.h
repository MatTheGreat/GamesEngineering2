#pragma once
#include <SDL.h>
#undef main
#include <thread>
#include <vector>
#include "RenderManager.h"
#include "RenderObject.h"
#include <iostream>

//Class to manager threads
//Will put thread pooling code here at later date
class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();
	void Render(RenderManager* renderManager, std::vector<RenderObject*> renderObjs);
private:
	SDL_Thread *threadOne;
	SDL_Thread *threadTwo;

	std::vector<std::pair<void *, int>>* dataOne;
	std::vector<RenderObject*>* objsOne;
	 
	std::vector<std::pair<void *, int>>* dataTwo;
	std::vector<RenderObject*>* objsTwo;
	int* idOne;
	int* idTwo;
};

