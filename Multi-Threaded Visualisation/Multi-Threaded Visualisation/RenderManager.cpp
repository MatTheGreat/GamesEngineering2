#include "RenderManager.h"

RenderManager::RenderManager(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

RenderManager::~RenderManager()
{

}

void RenderManager::DrawObject(RenderObject* object)
{
	SDL_RenderCopy(m_renderer, object->getTexture(), object->getSourceRect(), object->getDestRect());
}