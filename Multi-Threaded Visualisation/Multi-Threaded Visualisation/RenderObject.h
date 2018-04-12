#pragma once
#include <SDL.h>

class RenderObject
{
public:
	RenderObject(SDL_Texture * texture, int sourceX, int sourceY, int sourceWidth, int sourceHeight, int destX, int destY, int destWidth, int destHeight, int nodeID);
	~RenderObject();
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* texture);
	SDL_Rect* getSourceRect();
	SDL_Rect* getDestRect();
	int m_nodeID;
private:
	SDL_Texture* m_texture;
	SDL_Rect * m_sourceRect;
	SDL_Rect * m_destRect;
};

