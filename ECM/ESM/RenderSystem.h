#pragma once
#include "Entity.h"

#include "PositionComponent.h"

#include <vector>
#include <memory>

class RenderSystem
{
	std::vector<Entity*> entities;
public:

	RenderSystem();
	~RenderSystem();
	void addEntity(Entity* e);
	void Update();

private:

};