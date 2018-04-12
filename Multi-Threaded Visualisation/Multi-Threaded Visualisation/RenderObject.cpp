#include "RenderObject.h"

RenderObject::RenderObject(SDL_Texture * texture, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int destX, int destY, int destWidth, int destHeight, int nodeID)
{
	m_texture = texture;
	m_sourceRect = new SDL_Rect();
	m_sourceRect->x = sourceX;
	m_sourceRect->y = sourceY;
	m_sourceRect->w = sourceWidth;
	m_sourceRect->h = sourceHeight;

	m_destRect = new SDL_Rect();
	m_destRect->x = destX;
	m_destRect->y = destY;
	m_destRect->w = destWidth;
	m_destRect->h = destHeight;

	m_nodeID = nodeID;
}

RenderObject::~RenderObject()
{

}

SDL_Texture * RenderObject::getTexture()
{
	return m_texture;
}

void RenderObject::setTexture(SDL_Texture * texture)
{
	m_texture = texture;
}

SDL_Rect * RenderObject::getSourceRect()
{
	return m_sourceRect;
}

SDL_Rect * RenderObject::getDestRect()
{
	return m_destRect;
}
