#pragma once
#include "SDL.h"
#include "RenderObject.h"

class RenderManager
{
public:
	RenderManager(SDL_Renderer* renderer);
	~RenderManager();
	void DrawObject(RenderObject* object);
private:
	SDL_Renderer* m_renderer;
};

