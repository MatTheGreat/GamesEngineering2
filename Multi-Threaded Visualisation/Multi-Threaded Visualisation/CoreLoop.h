#pragma once
#include "RenderObject.h"
#include "RenderManager.h"
#include "Graph.h"
#include "Agent.h"
#include "ThreadManager.h"
#include <iostream>
#include <fstream>

#include <SDL.h>
#undef main
#include <SDL_image.h>





class CoreLoop
{
public:
	CoreLoop();
	~CoreLoop();
	void RunAStar();
	bool Loop();
	void Update();
	void Draw();
	void GenerateMap();
	void OutputPath(std::vector<Node*> path, int startIndex);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	RenderManager* renderManager;
	std::vector <RenderObject*> renderObjs; // temp variable for test
	ThreadManager* threadManager;
	Graph graph;
	bool isRunning;


	SDL_Thread *thread;
	std::vector<Agent*> agents;
	std::vector<std::pair<void *, int>>* data;
	int start = 17;
	int end = 151;
};
