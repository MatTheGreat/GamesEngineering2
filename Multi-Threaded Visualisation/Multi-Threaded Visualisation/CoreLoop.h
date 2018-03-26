#pragma once

#include "Graph.h"
#include <iostream>
#include <fstream>
#include "Agent.h"
#include <SDL.h>
#undef main

class CoreLoop
{
public:
	CoreLoop();
	~CoreLoop();
	void RunAStar(Graph graph);
	bool Loop();
	void Update();
	void Draw();
	void GenerateMap();
	void OutputPath(std::vector<Node*> path, int startIndex);
private:
	SDL_Window* window;
	Graph graph;
	bool isRunning;
};
